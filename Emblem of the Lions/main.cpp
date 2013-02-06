#include "region.h"

#include "SDL.h"

#include <iostream>

using namespace std;

int SDL_main(int, char**) {
	Region region;

	region.NewData(40, 40, 3);
	region.SaveData("region.txt");
	region.SaveData("region (raw).txt");
	region.DeleteData();

	return 0;
}