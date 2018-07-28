#include <iostream>
#include "MapReader.h"

int main(void)
 {
	MapReader map;

	if (!map.MapUpload(L"near.osm"))
		std::cout << "Failed To Map upload." << std::endl;
	std::cout << std::endl;
	system("pause");

	return 0;
}