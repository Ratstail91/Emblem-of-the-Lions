#include "map_utility.h"

#include "SDL.h"

#include <stdexcept>
#include <iostream>

using namespace std;

#include <direct.h>
#include <dirent.h>

int SDL_main(int, char**) {
	try {
/*		cout << "Creating the map object" << endl;
		MapUtility map;

		cout << "Creating the new map" << endl;
		map.NewMap("foo", 50, 40, 3);

		cout << "Freeing the map" << endl;
		map.FreeMap();

		cout << "Loading the map again" << endl;
		map.LoadMap("foo");

		cout << "Loaded map data:" << endl;
		cout << "Map name: " << map.GetMapName() << endl;
		cout << "RegionX: " << map.GetRegionX() << endl;
		cout << "RegionY: " << map.GetRegionY() << endl;
		cout << "RegionZ: " << map.GetRegionZ() << endl;

		cout << "Freeing the map again" << endl;
		map.FreeMap();

		cout << "Deleting the map" << endl;
		map.DeleteMap("foo");

		cout << "Creating another map" << endl;
		map.NewMap("bar", 5, 5, 5);

		cout << "Freeing the new map" << endl;
		map.FreeMap();

		cout << "delete that map" << endl;
		map.DeleteMap("bar");
*/
		MapUtility map;

		cout << "Deleting previous version..." << endl;
		map.DeleteMap("foo");

		cout << "new" << endl;
		map.NewMap("foo", 42, 36, 3);

		cout << "save" << endl;
		map.SaveMap();

		cout << "free" << endl;
		map.FreeMap();

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