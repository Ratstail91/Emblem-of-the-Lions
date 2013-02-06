#ifndef KR_REGION_H_
#define KR_RAGION_H_

#include "SDL.h"

class Region {
public:
	Region();
	~Region();

	void LoadData(const char* fname);
	void SaveData(const char* fname);

	void NewData(Uint16 x, Uint16 y, Uint16 z);
	void DeleteData();

	Uint16 SetTile(Uint16 x, Uint16 y, Uint16 z, Uint16 v);
	Uint16 GetTile(Uint16 x, Uint16 y, Uint16 z);

	Uint16 GetX();
	Uint16 GetY();
	Uint16 GetZ();
	
	Uint16 operator++(void);
	bool end(void);
	bool rewind(void);
	

private:
	Uint16 xCount, yCount, zCount;
	// you shouldn't even need a ** unless you want to pass by-reference-to-reference, whoever told you
	// that *** is a "3D array" needs to be taken out back and shot.
	Uint16 *data;
	Uint16 *iterator;
};

#endif
