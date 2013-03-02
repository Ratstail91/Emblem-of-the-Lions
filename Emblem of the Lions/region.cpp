#include "region.h"

#include <stdexcept>
#include <fstream>

Region::Region() {
	indexX = indexY = 0;
	width = height = depth = size = 0;
	data = NULL;
}

Region::~Region() {
	Unload();
}

void Region::Load(const char* fname) {
	if (data != NULL)
		Unload();

	std::ifstream is(fname);

	if (!is.is_open())
		throw(std::runtime_error("Failed to load region data"));

	//load the format data
	is >> width;
	is >> height;
	is >> depth;
	size = width * height * depth;

	if (size == 0) {
		is.close();
		throw(std::runtime_error("No region data to load or region format is corrupted"));
	}

	New(width, height, depth);

	//NOTE, TODO: This is probably a temporary format
	//load the raw data
	Region::iterator it = Begin();
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < depth; k++) {
				it->x = i;
				it->y = j;
				it->z = k;
				is >> it->val;
				it++;
			}
		}
	}

	is.close();
}

void Region::Save(const char* fname) {
	if (data == NULL)
		throw(std::logic_error("No region data to save"));

	std::ofstream os(fname);

	if (!os.is_open())
		throw(std::runtime_error("Failed to save region data"));

	//save the format data
	os << width << " " << height << " " << depth << std::endl;

	//save the raw data
	Region::iterator it = Begin();
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < depth; k++) {
				os << it->val << " ";
				it++;
			}
			os << "\t";
		}
		os << std::endl;
	}

	os.close();
}

void Region::New(int x, int y, int z) {
	if (data != NULL)
		Unload();

	width = x;
	height = y;
	depth = z;
	size = width * height * depth;

	data = new Tile[size];

/*	//DEBUG: test data
	int i = 0;
	for (Tile::iterator it = Begin(); it != End(); it++, i++) {
		it->val = i;
	}*/
}

void Region::Unload() {
	delete[] data;
	width = height = depth = size = 0;
	data = NULL;
}

Tile* Region::SetTile(int x, int y, int z, int v) {
	if (data == NULL)
		throw(std::logic_error("No region data to set"));

	//range is 0 to x - 1 inclusive, where x is the specified dimension
	if (x >= width || y >= height || z >= depth || x < 0 || y < 0 || z < 0)
		throw(std::out_of_range("Specified tile index is out of range"));

	//NOTE: data is stored as though it were data[x][y][z]
	int pos = (x * height * depth) + (y * depth) + z;
	(data + pos)->val = v;

	return data + pos;
}

Tile* Region::GetTile(int x, int y, int z) {
	if (data == NULL)
		throw(std::logic_error("No region data to retrieve"));

	//range is 0 to x - 1 inclusive, where x is the specified dimension
	if (x >= width || y >= height || z >= depth || x < 0 || y < 0 || z < 0)
		throw(std::out_of_range("Specified tile index is out of range"));

	//NOTE: data is stored as though it were data[x][y][z]
	return data + (x * height * depth) + (y * depth) + z;
}

int Region::GetWidth() const {
	return width;
}

int Region::GetHeight() const {
	return height;
}

int Region::GetDepth() const {
	return depth;
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
