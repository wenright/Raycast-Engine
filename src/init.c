#include "init.h"

int init_SDL() {
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else {
		//Create window
		window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_BORDERLESS);
		if(window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}

		//Get window surface
		screen = SDL_GetWindowSurface(window);
		if (screen == NULL)
			printf("Failed to set screen. SDL error: %s\n", SDL_GetError());
	}

	//Hide/lock cursor
	SDL_ShowCursor(false);
	SDL_SetRelativeMouseMode(true);
	return true;
}

int loadMedia() {
	//Load wall textures
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		//Allocate enough space for file path (and then some, in case someone wants to use 99999 textures)
		char *imagePath = malloc(24);
		sprintf(imagePath, "images/texture%d.bmp", i);

		textureSource[i] = SDL_LoadBMP(imagePath);
		if(textureSource[i] == NULL) {
			printf("Unable to load images/texture%d.bmp, SDL Error: %s\n", i, SDL_GetError());
			free(imagePath);
			return false;
		}

		free(imagePath);
	}

	return true;
}

void close_SDL() {
	//Deallocate surfaces
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		SDL_FreeSurface(textureSource[i]);
		textureSource[i] = NULL;
	}

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}