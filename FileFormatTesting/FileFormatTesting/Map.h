#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <limits>

#include <map>

#include "CustomFormat.h"

class Map
{
public:
	Map();
	Map(std::string filename);
	Map(std::string filename, std::string title, int height, int width);

	bool Save(std::string filename);
	bool Save();

	bool Load(std::string filename);

	bool AddTile(std::string filename, bool collides, int width, int height, int charcode);

	bool Error() { return hasErrors; }
	std::string ErrorDesc() { return error; }

	void PrintInfo();

private:
	bool CheckHeader(MAPFILEHEADER mh);
	bool DoError(std::string error);
	int GetRemainingBytes(std::ifstream& ifs);

	MAPFILEHEADER mapHeader;
	std::map<char, TILEINFO> tiles;
	std::map<char, std::string> tilePaths;
	std::string curFilename;
	std::string mapTitle;

	bool hasErrors;
	std::string error;

	int mWidth, mHeight;

};

#endif