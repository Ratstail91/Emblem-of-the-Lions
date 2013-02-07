#ifndef KR_MAPUTILITY_H_
#define KR_MAPUTILITY_H_

#include "region.h"

#include <vector>
#include <string>

class MapUtility {
public:
	MapUtility();
	~MapUtility();

	void LoadMap(const char* mapname);
	void SaveMap(const char* mapname);
	void NewMap(const char* mapname, int regionX, int regionY, int regionZ);
	void DeleteMap(); //TODO: make the distinction between freeing and deleting a map


	//control the list of Regions
	void NewRegion(int indexX, int indexY);
	void LoadRegion(int indexX, int indexY);
	void SaveRegion(int indexX, int indexY);
	void UnloadRegion(int indexX, int indexY);
	Region* GetRegion(int indexX, int indexY);

	void CullMap(int centerX, int centerY, int min = 1, int max = 2);

	Tile* SetTile(int x, int y, int z, int v);
	Tile* GetTile(int x, int y, int z);

private:
	int regionX, regionY, regionZ;
	std::vector<Region*> regionList;
	std::string mapName;
};

#endif
