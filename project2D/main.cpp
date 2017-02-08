#include "Application2D.h"
#include "Level.h"//Add level for screen size.

int main() {
	
	auto app = new Application2D();
	app->run("AIE", MAP_SIZE_X * MAP_CELLSIZE_X, MAP_SIZE_Y * MAP_CELLSIZE_Y, false);
	delete app;

	return 0;
}