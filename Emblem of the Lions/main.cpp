#include "map_utility.h"

#include "SDL.h"

#include <stdexcept>
#include <iostream>

using namespace std;

int SDL_main(int, char**) {
/*	Region region;

	region.NewData(40, 40, 3);
	region.SaveData("region.txt");
	region.SaveData("region (raw).txt");
	region.DeleteData();
*/
	MapUtility map;

	try {
		cout << "Creating a new map" << endl;
		map.NewMap("mapname", 40, 40, 3);

		cout << "Saving the map" << endl;
		map.SaveMap("mapname");

		cout << "Freeing the existing map" << endl;
		map.DeleteMap();

		cout << "Loading the map again" << endl;
		map.LoadMap("mapname");

		cout << "Finally freeing the map again before closing" << endl;
		map.DeleteMap();
	}
	catch(runtime_error& e) {
		cerr << "Runtime Error: " << e.what() << endl;
		map.DeleteMap();
		return -1;
	}
	catch (exception& e) {
		cerr << "Error: " << e.what() << endl;
		map.DeleteMap();
		return -2;
	}

	cout << "Remember to delete the map files before runningthis test again." << endl;

	return 0;
}