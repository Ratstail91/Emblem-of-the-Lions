#ifndef KR_REGION_H_
#define KR_RAGION_H_

#include "tile.h"

class Region {
public:
	Region();
	~Region();

	void Load	(const char* fname);
	void Save	(const char* fname);
	void New	(int width, int height, int depth);
	void Unload	();

	Tile* SetTile(int x, int y, int z, int v);
	Tile* GetTile(int x, int y, int z);

	int GetWidth() const;
	int GetHeight() const;
	int GetDepth() const;
	int GetSize() const;

	int SetIndexX(int);
	int SetIndexY(int);
	int GetIndexX() const;
	int GetIndexY() const;

	//TODO: C++11 compat
	Tile* Begin() const;
	Tile* End() const;
	typedef Tile* iterator;

private:
	int indexX, indexY;
	int width, height, depth, size;
	Tile* data;
};

#endif
