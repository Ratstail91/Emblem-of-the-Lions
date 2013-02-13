#include "map.h"

#include "SDL.h"

#include <stdexcept>
#include <iostream>

using namespace std;

int SDL_main(int, char**) {
	try {
		cout << "Creating the map object" << endl;
		Map map;

		cout << "Deleting any previous map" << endl;
		map.Delete("foo");

		cout << "Creating the new map" << endl;
		map.New("foo", 50, 40, 3);

		cout << "Freeing the map" << endl;
		map.Free();

		cout << "Loading the map again" << endl;
		map.Load("foo");

		cout << "Loaded map data:" << endl;
		cout << "Map name: " << map.GetName() << endl;
		cout << "RegionX: " << map.GetRegionX() << endl;
		cout << "RegionY: " << map.GetRegionY() << endl;
		cout << "RegionZ: " << map.GetRegionZ() << endl;

		cout << "Freeing the map again" << endl;
		map.Free();

		cout << "Test completed." << endl;
	}
	catch(runtime_error& e) {
		cerr << "Runtime Error: " << e.what() << endl;
		return -1;
	}
	catch(exception& e) {
		cerr << "Error: " << e.what() << endl;
		return -2;
	}

	return 0;
}