#include "map.h"

#include <stdexcept>
#include <fstream>

#include <dirent.h>

Map::Map() {
	regionX = regionY = regionZ = 0;
}

Map::~Map() {
	Free();
}

void Map::New(const char* mapdir, int x, int y, int z) {
	if (!_chdir(n)) {
		_chdir("..");
		throw(std::runtime_error("A map of this name already exists"));
	}

	_mkdir(n);

	mapName = n;

	regionX = x;
	regionY = y;
	regionZ = z;

	Save();

	//debug
	regionList.push_back(new Region());

	regionList[0]->NewData(regionX, regionY, regionZ);
}

void Map::Load(const char* mapdir) {
	if (_chdir(n))
		throw(std::runtime_error("Failed to load the named map"));

	std::ifstream is("index.txt");

	if (!is.is_open()) {
		_chdir("..");
		throw(std::runtime_error("Failed to load the map data"));
	}

	if (regionX || regionY || regionZ)
		Free();

	mapName = n;

	is >> regionX;
	is >> regionY;
	is >> regionZ;

	is.close();
	_chdir("..");

	//the next step is to load the regions independantly
}

void Map::Save() {
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
		(*it)->SaveData(buffer);
	}

	os.close();
	_chdir("..");
}

void Map::Free() {
	regionX = regionY = regionZ = 0;
	mapName.clear();
	for (std::vector<Region*>::iterator it = regionList.begin(); it != regionList.end(); it++) {
		(*it)->DeleteData();
		delete (*it);
	}
	regionList.clear();
}

void Map::Delete(const char* mapdir) {
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

void Map::NewRegion(int indexX, int indexY) {
	//TODO
}

void Map::LoadRegion(int indexX, int indexY) {
 	//TODO
 }

void Map::SaveRegion(int indexX, int indexY) {
	//TODO
}

void Map::UnloadRegion(int indexX, int indexY) {
	//TODO
}

Region* Map::GetRegion(int indexX, int indexY) {
	//TODO
}

Tile* Map::SetTile(int x, int y, int z, int v) {
	//TODO
}

Tile* Map::GetTile(int x, int y, int z) {
	//TODO
}

int Map::GetRegionX() const {
	return regionX;
}

int Map::GetRegionY() const {
	return regionY;
}

int Map::GetRegionZ() const {
	return regionZ;
}

std::string Map::GetName() const {
	return mapName;
}
