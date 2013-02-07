#ifndef KR_TILE_H_
#define KR_TILE_H_

//These members are public; rule of good enough

class Tile {
public:
	Tile() {
		x = y = z = val = 0;
	}

	int x, y, z;
	int val;

	typedef Tile* iterator;
};

#endif
