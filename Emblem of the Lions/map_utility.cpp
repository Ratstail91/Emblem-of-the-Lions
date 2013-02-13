#include "map_utility.h"

#include <stdexcept>
#include <fstream>

#include <direct.h>
#include <dirent.h>

//*debug
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
//*/

MapUtility::MapUtility() {
	regionX = regionY = regionZ = 0;
}

MapUtility::~MapUtility() {
	FreeMap();
}

void MapUtility::NewMap(const char* n, int x, int y, int z) {
	if (!_chdir(n)) {
		_chdir("..");
		throw(std::runtime_error("A map of this name already exists"));
	}

	_mkdir(n);

	mapName = n;

	regionX = x;
	regionY = y;
	regionZ = z;

	SaveMap();

	//debug
	regionList.push_back(new Region());

	regionList[0]->NewData(regionX, regionY, regionZ);
}

void MapUtility::LoadMap(const char* n) {
	if (_chdir(n))
		throw(std::runtime_error("Failed to load the named map"));

	std::ifstream is("index.txt");

	if (!is.is_open()) {
		_chdir("..");
		throw(std::runtime_error("Failed to load the map data"));
	}

	if (regionX || regionY || regionZ)
		FreeMap();

	mapName = n;

	is >> regionX;
	is >> regionY;
	is >> regionZ;

	is.close();
	_chdir("..");

	//the next step is to load the regions independantly
}

void MapUtility::SaveMap() {
	if (_chdir(mapName.c_str())) {
		throw(std::runtime_error("Failed to save the map"));
	}

	std::ofstream os("index.txt");

	if (!os.is_open()) {
		_chdir("..");
		throw(std::runtime_error("Failed to save the map index"));
	}

	os << regionX << " ";
	os << regionY << " ";
	os << regionZ << " ";

	//other metadata later

	char buffer[128];
	for (std::vector<Region*>::iterator it = regionList.begin(); it != regionList.end(); it++) {
		sprintf(buffer, "%d.%d.region", (*it)->GetIndexX(), (*it)->GetIndexY());

		cout << "region name: " << buffer << endl;

		(*it)->SaveData(buffer);
	}

	os.close();
	_chdir("..");
}

void MapUtility::FreeMap() {
	regionX = regionY = regionZ = 0;
	mapName.clear();
	for (std::vector<Region*>::iterator it = regionList.begin(); it != regionList.end(); it++) {
		(*it)->DeleteData();
		delete (*it);
	}
	regionList.clear();
}

void MapUtility::DeleteMap(const char* n) {
	if (mapName == n) {
		//could add a locking system later
		throw(std::logic_error("Cannot delete a map that is currently opened"));
	}

	if (_chdir(n)) {
		//just a simple return, if there's no map to delete, just assume it has been deleted
		return;
//		throw(std::runtime_error("No map of this name to delete"));
	}

	DIR* dir = opendir(".");
	dirent* ent;

	while(ent = readdir(dir)) {
		if (ent->d_type == DT_REG)
			remove(ent->d_name);
	}

	closedir(dir);
	_chdir("..");
	_rmdir(n);
}

void MapUtility::NewRegion(int indexX, int indexY) {
	//TODO
}

void MapUtility::LoadRegion(int indexX, int indexY) {
 	//TODO
 }

void MapUtility::SaveRegion(int indexX, int indexY) {
	//TODO
}

void MapUtility::UnloadRegion(int indexX, int indexY) {
	//TODO
}

Region* MapUtility::GetRegion(int indexX, int indexY) {
	//TODO
}

void MapUtility::CullMap(int centerX, int centerY, int min, int max) {
	//TODO
}

Tile* MapUtility::SetTile(int x, int y, int z, int v) {
	//TODO
}

Tile* MapUtility::GetTile(int x, int y, int z) {
	//TODO
}

int MapUtility::GetRegionX() const {
	return regionX;
}

int MapUtility::GetRegionY() const {
	return regionY;
}

int MapUtility::GetRegionZ() const {
	return regionZ;
}

std::string MapUtility::GetMapName() const {
	return mapName;
}
