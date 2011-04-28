#include "Map.h"

Map::Map()
{
}

Map::Map(std::string filename, std::string title, int height, int width)
{
	curFilename = filename;
	mapTitle = title;
	mapHeader.chHeader = HEADER;
	mapHeader.chHeight = height;
	mapHeader.chWidth = width;
	mapHeader.chSize = sizeof(MAPFILEHEADER);

	// Add 1 so we have a null terminator.
	mapHeader.chTitleLength = title.size() + 1;

	hasErrors = false;
}

Map::Map(std::string filename)
{
	if (!Load(filename))
	{
		return;
	}

	hasErrors = false;
}

bool Map::AddTile(std::string filename, bool collides, int width, int height, int charcode)
{
	TILEINFO tile;
	// Add 1 so we have a null terminating end to it when it is written to file.
	tile.tiPathLength = filename.size() + 1;
	tile.tiCollides = collides;
	tile.tiWidth = width;
	tile.tiHeight = height;
	tile.tiVar = charcode;

	if (tiles.find(charcode) != tiles.end())
		return DoError("Character code has already been added.");

	if (charcode > CHAR_MAX || charcode < CHAR_MIN)
		return DoError("Character code out of bounds. -127 <= cc <= 127.");

	tiles[(char)charcode] = tile;
	tilePaths[(char)charcode] = filename;

	return true;
}

bool Map::Save(std::string filename)
{
	std::ofstream ofs;
	ofs.open(filename.c_str());

	if (!ofs.is_open() || ofs.fail())
		return DoError("Error in saving the map file. Could not open file.");

	if (mapHeader.chHeader != HEADER)
		return DoError("Map has not been created. Header is invalid.");
	
	// Update the number of tiles:
	mapHeader.chNumTiles = tiles.size();

	// Write the header and the title.
	ofs.write((char*)&mapHeader, sizeof(MAPFILEHEADER));
	ofs.write(mapTitle.c_str(), mapHeader.chTitleLength);

	// Write the map's tiles.
	std::map<char, TILEINFO>::iterator i = tiles.begin();
	for (int k = 0; (k < mapHeader.chNumTiles && i != tiles.end()); i++, k++)
	{
		TILEINFO currentTile = i->second;

		// Write the tile info.
		ofs.write((char*)&currentTile, sizeof(TILEINFO));
		ofs.write(tilePaths[i->first].c_str(), currentTile.tiPathLength);

		if (ofs.fail())
			return DoError("Error writing the tile information to the file.");
	}

	// Write the map info.
	// TODO: Create map info.

	ofs.close();

	return true;
}

bool Map::Save()
{
	return Save(curFilename);
}

void Map::PrintInfo()
{
	std::cout << "Map Filename: " << curFilename.c_str() << '\n';
	std::cout << "Map Title: " << mapTitle.c_str() << '\n';
	std::cout << "Height: " << mapHeader.chHeight << " Width: " << mapHeader.chWidth << '\n';
	std::cout << "Number of Tiles: " << mapHeader.chNumTiles << '\n';
	std::cout << '\n' << "============================TILES============================" << '\n';

	std::map<char, TILEINFO>::iterator i = tiles.begin();
	for (int k = 0; i != tiles.end(); i++, k++)
	{
		TILEINFO cur = i->second;
		std::cout << "Tile ID: " << k << '\n';
		std::cout << "Char Code:" << i->first << " Filename: " << tilePaths[i->first].c_str() << '\n';
		std::cout << "Collides: " << cur.tiCollides << '\n';
		std::cout << "Height: " << cur.tiHeight << " Width: " << cur.tiWidth << '\n';
		std::cout << "===============================================================" << '\n';
	}
}

bool Map::Load(std::string filename)
{
	curFilename = filename;

	std::ifstream ifs;
	ifs.open(filename.c_str());

	if (!ifs.is_open())
		return DoError("Could not find file.");

	// Read in the header.
	ifs.read((char*)&mapHeader, sizeof(MAPFILEHEADER));

	// Check the header.
	if (!CheckHeader(mapHeader) || ifs.fail())
		return DoError("Malformed map header!");

	// Read in the map title.
	char* title = new char[mapHeader.chTitleLength];
	ifs.read(title, mapHeader.chTitleLength);
	mapTitle = title;
	title = NULL;

	if (ifs.fail())
		return DoError("Error loading the map title.");

	// Grab our tiles
	for (int i = 0; i < mapHeader.chNumTiles; i++)
	{
		TILEINFO currentTile;
		ifs.read((char*)&currentTile, sizeof(TILEINFO));

		// Read the tile path:
		char* path = new char[currentTile.tiPathLength];
		ifs.read(path, currentTile.tiPathLength);

		if (ifs.fail())
			return DoError("Error in loading the tiles.");
		tiles[(char)currentTile.tiVar] = currentTile;
		tilePaths[(char)currentTile.tiVar] = std::string(path);

		path = NULL;
	}

	// Read in the map contents.
	// TODO: Create map contents.

	ifs.close();

	return true;
}

bool Map::CheckHeader(MAPFILEHEADER mh)
{
	if (mh.chHeader != HEADER || mh.chSize != sizeof(MAPFILEHEADER))
		return false;
	return true;
}

bool Map::DoError(std::string errorcode)
{
	hasErrors = true;
	error = errorcode;
	return false;
}

int Map::GetRemainingBytes(std::ifstream& ifs)
{
	// Calculate the size remaining.
	std::ios::streampos cur = ifs.tellg();
	ifs.seekg(cur, std::ios::end);
	std::ios::streampos size = cur - ifs.tellg();

	// Put as back where we were before.
	ifs.seekg(std::ios::beg, cur);

#if DEBUG
	if (ifs.tellg() != cur)
		return 0;
#endif

	return (int)size;
}
