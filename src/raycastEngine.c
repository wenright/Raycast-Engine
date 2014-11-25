#include "include/raycastEngine.h"

int main(int argc, char* args[]) {
	//Initialize SDL and media files
	if (!init_SDL() || !loadMedia())
		return 1;

	generateMap ();

	//Loop until exit signal is received
	while (handleInput ()) {
		//Clear the screen
		SDL_FillRect(screen, NULL, RGB_White);

		//Raycast for map blocks
		renderWalls ();

		//Update surface
		SDL_UpdateWindowSurface (window);

		//Calculate FPS, delay to maintain 60 fps
		double deltaTime = calcFPS ();

		//Move player using input received from above
		movePlayer (deltaTime);
	}

	//Exit
	close_SDL();

	return 0;
}