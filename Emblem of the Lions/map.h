#ifndef KR_MAP_H_
#define KR_MAP_H_

#include "region.h"

#include <vector>
#include <string>

class Map {
public:
	Map();
	~Map();

	void New(const char* mapname, int regionX, int regionY, int regionZ);
	void Load(const char* mapname);
	void Save();
	void Free();
	void Delete(const char* mapname);

	//control the list of Regions
	void NewRegion(int indexX, int indexY);
	void LoadRegion(int indexX, int indexY);
	void SaveRegion(int indexX, int indexY);
	void UnloadRegion(int indexX, int indexY);
	Region* GetRegion(int indexX, int indexY);

	Tile* SetTile(int x, int y, int z, int v);
	Tile* GetTile(int x, int y, int z);

	int GetRegionX() const;
	int GetRegionY() const;
	int GetRegionZ() const;

	std::string GetName() const;

private:
	int regionX, regionY, regionZ;
	std::vector<Region*> regionList;
	std::string mapName;
};

#endif
