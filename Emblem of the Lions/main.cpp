#include "region.h"

#include "SDL.h"

//debugging
#include <stdexcept>
#include <iostream>

using namespace std;

int SDL_main(int, char**) {
	try {
		Region r;

		r.New(10, 10, 2);
		r.SetTile(3,0,0,42);
		r.Save("region.txt");

		r.Load("region.txt");
		cout << "--test: " << r.GetTile(3, 0, 0)->val << ", " << r.GetTile(0, 3, 0)->val << endl;
		r.Save("region2.txt");

		r.Unload();
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
