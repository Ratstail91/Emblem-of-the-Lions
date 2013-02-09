#include "map_utility.h"

#include <stdexcept>
#include <fstream>

#include <direct.h>

MapUtility::MapUtility() {
	regionX = regionY = regionZ = 0;
}

MapUtility::~MapUtility() {
	FreeMap();
}

void MapUtility::LoadMap(const char* n) {
	if (regionX || regionY || regionZ)
		FreeMap();

	mapName = n;

	std::ifstream is((mapName + "/index.txt").c_str());

	if (!is.is_open())
		throw(std::runtime_error("Failed to load the map data"));

	//TODO

	is.close();

	//TODO
}

void MapUtility::SaveMap(const char* newName) {
	if (!regionX || !regionY || !regionZ)
		throw(std::logic_error("No map data to save"));

	_mkdir(newName);
	std::ofstream os((std::string(newName) + "/index.txt").c_str());

	if (!os.is_open())
		throw(std::runtime_error("Failed to save the map data"));

	//TODO

	os.close();

	//TODO
}

void MapUtility::NewMap(const char* n, int x, int y, int z) {
	if (regionX || regionY || regionZ)
		FreeMap();

	mapName = n;

	_mkdir(mapName.c_str());
	std::ifstream is((mapName + "/index.txt").c_str());

	if (is.is_open()) {
		is.close();
		mapName.clear();
		throw(std::runtime_error("A map of this name already exists"));
	}

	regionX = x;
	regionY = y;
	regionZ = z;
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

void MapUtility::DeleteMap(const char* mapname) {
	//TODO
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
