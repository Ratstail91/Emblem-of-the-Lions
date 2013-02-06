#ifndef KR_REGION_H_
#define KR_RAGION_H_

#include "tile.h"

class Region {
public:
	Region();
	~Region();

	void LoadData(const char* fname);
	void SaveData(const char* fname);

	void NewData(int x, int y, int z);
	void DeleteData();

	Tile::iterator SetTile(int x, int y, int z, int v);
	Tile::iterator GetTile(int x, int y, int z);

	int GetX() const;
	int GetY() const;
	int GetZ() const;
	int GetSize() const;

	Tile::iterator Begin() const;
	Tile::iterator End() const;

private:
	int xCount, yCount, zCount, size;
	Tile* data;
};

#endif
