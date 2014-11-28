#include "include/raycastEngine.h"

int main(int argc, char* args[]) {
	if (!init_SDL() || !loadMedia())
		return 1;

	generateRandomMap();

	while (handleInput ()) {
		renderSky ();

		renderFloor ();

		renderWalls ();

		SDL_UpdateWindowSurface (window);

		movePlayer (calcFPS ());
	}

	close_SDL();

	return 0;
}