#ifndef KR_MAPPERSISTER_H_
#define KR_MAPPERSISTER_H_

#include "tile.h"

#include "SDL.h"

class MapPersister {
public:
	virtual ~MapPersister() {};

	virtual void Load	(const char* name) = 0;
	virtual void Save	() = 0;
	virtual void New	(const char* name, ...) = 0;
	virtual void Delete	(const char* name) = 0;
	virtual void Unload	() = 0;

	virtual void Cull	(int playerX, int playerY) = 0;

	virtual void DrawTo(SDL_Surface* dest, int camX, int camY) = 0;
	virtual Tile* SetTile(int x, int y, int z, int v) = 0;
	virtual Tile* GetTile(int x, int y, int z) = 0;
};

#endif
