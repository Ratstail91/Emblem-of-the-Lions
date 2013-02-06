#ifndef KR_TILE_H_
#define KR_TILE_H_

//These members are public; rule of good enough

class Tile {
public:
	Tile() {
		x = y = val = 0;
	}

	int x, y;
	int val;

	typedef Tile* iterator;
};

#endif
