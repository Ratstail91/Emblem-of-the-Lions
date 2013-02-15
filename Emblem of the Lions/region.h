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

	Tile* SetTile(int x, int y, int z, int v);
	Tile* GetTile(int x, int y, int z);

	int GetX() const;
	int GetY() const;
	int GetZ() const;
	int GetSize() const;

	int SetIndexX(int);
	int SetIndexY(int);
	int GetIndexX() const;
	int GetIndexY() const;

	Tile* Begin() const;
	Tile* End() const;
	typedef Tile* iterator;

private:
	int indexX, indexY;
	int xCount, yCount, zCount, size;
	Tile* data;
};

#endif
