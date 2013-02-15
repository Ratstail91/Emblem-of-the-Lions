#include "region.h"

#include <stdexcept>
#include <fstream>

Region::Region() {
	indexX = indexY = 0;
	xCount = yCount = zCount = size = 0;
	data = NULL;
}

Region::~Region() {
	DeleteData();
}

void Region::LoadData(const char* fname) {
	if (data != NULL)
		DeleteData();

	std::ifstream is(fname);

	if (!is.is_open())
		throw(std::runtime_error("Failed to load region data"));

	//load the format data
	is >> xCount;
	is >> yCount;
	is >> zCount;
	size = xCount * yCount * zCount;

	if (size == 0) {
		is.close();
		throw(std::runtime_error("No region data to load or region format is corrupted"));
	}

	NewData(xCount, yCount, zCount);

	//NOTE: This doesn't use a ranged based loop to make sure the x & y values are set
	//NOTE, TODO: This is probably a temporary format
	Region::iterator it = Begin();
	for (int i = 0; i < xCount; i++) {
		for (int j = 0; j < yCount; j++) {
			for (int k = 0; k < zCount; k++) {
				it->x = i;
				it->y = j;
				it->z = k;
				is >> it->val;
			}
		}
	}

	is.close();
}

void Region::SaveData(const char* fname) {
	if (data == NULL)
		throw(std::logic_error("No region data to save"));

	std::ofstream os(fname);

	if (!os.is_open())
		throw(std::runtime_error("Failed to save region data"));

	//save the format data
	os << xCount << " " << yCount << " " << zCount << std::endl;

	//save the raw data (y axis first)
	for (int j = 0; j < yCount; j++) {
		for (int i = 0; i < xCount; i++) {
			for (int k = 0; k < zCount; k++) {
				os << GetTile(i,j,k)->val << " ";
			}
			os << " ";
		}
		os << std::endl;
	}

	os.close();
}

void Region::NewData(int x, int y, int z) {
	if (data != NULL)
		DeleteData();

	xCount = x;
	yCount = y;
	zCount = z;
	size = xCount * yCount * zCount;

	data = new Tile[size];

/*	//DEBUG: test data
	int i = 0;
	for (Tile::iterator it = Begin(); it != End(); it++, i++) {
		it->val = i;
	}*/
}

void Region::DeleteData() {
	delete[] data;
	xCount = yCount = zCount = size = 0;
	data = NULL;

}

Tile* Region::SetTile(int x, int y, int z, int v) {
	if (data == NULL)
		throw(std::logic_error("No region data to set"));

	//range is 0 to x - 1 inclusive, where x is the specified dimension
	if (x >= xCount || y >= yCount || z >= zCount || x < 0 || y < 0 || z < 0)
		throw(std::out_of_range("Specified tile index is out of range"));

	//NOTE: data is stored as though it were data[x][y][z]
	(data + (x * yCount * zCount) + (y * zCount) + z)->val = v;

	return data + (x * yCount * zCount) + (y * zCount) + z;
}

Tile* Region::GetTile(int x, int y, int z) {
	if (data == NULL)
		throw(std::logic_error("No region data to retrieve"));

	//range is 0 to x - 1 inclusive, where x is the specified dimension
	if (x >= xCount || y >= yCount || z >= zCount || x < 0 || y < 0 || z < 0)
		throw(std::out_of_range("Specified tile index is out of range"));

	//NOTE: data is stored as though it were data[x][y][z]
	return data + (x * yCount * zCount) + (y * zCount) + z;
}

int Region::GetX() const {
	return xCount;
}

int Region::GetY() const {
	return yCount;
}

int Region::GetZ() const {
	return zCount;
}

int Region::GetSize() const {
	return size;
}

int Region::SetIndexX(int x) {
	return indexX = x;
}

int Region::SetIndexY(int y) {
	return indexY = y;
}

int Region::GetIndexX() const {
	return indexX;
}

int Region::GetIndexY() const {
	return indexY;
}

Tile* Region::Begin() const {
	return data;
}

Tile* Region::End() const {
	return data + size;
}
