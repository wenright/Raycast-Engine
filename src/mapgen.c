#include "mapgen.h"

void generateMap () {
	//Generate borders
	for (int i = 0; i < MAP_WIDTH; ++i) {
		worldMap[i][0] = 1;
		worldMap[i][MAP_HEIGHT - 1] = 1;
	}
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		worldMap[0][i] = 1;
		worldMap[MAP_HEIGHT - 1][i] = 1;
	}

	//Generate random blocks with random textures
	for (int i = 1; i < MAP_WIDTH - 1; ++i)
		for (int j = 1; j < MAP_HEIGHT - 1; ++j)
			if (rand() % 2)
				if (rand() % 2)
					worldMap[i][j] = (rand() % NUM_TEXTURES);
}