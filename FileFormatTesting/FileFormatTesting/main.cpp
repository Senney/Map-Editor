#include <fstream>
#include <iostream>
#include <string>

#include "CustomFormat.h"
#include "Map.h"
#include "MapEditor.h"

int main()
{
	Map loadMap("TestFormat.cf");
	if (loadMap.Error())
		std::cout << loadMap.ErrorDesc() << '\n';
	loadMap.PrintInfo();

	MapEditor newEditor;
	newEditor.Run();

	return 1;
}