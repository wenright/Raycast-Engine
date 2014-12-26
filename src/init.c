#include "include/init.h"

int init_SDL() {
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	/*
	SDL_DisplayMode displayMode;
	if (SDL_GetCurrentDisplayMode(i, &displayMode) != 0) {
		printf("Failed to find current resolution\n");
		return false;
	}
	SCREEN_WIDTH = displayMode.w;
	SCREEN_HEIGHT = displayMode.h;
	*/

	//Create window
	window = SDL_CreateWindow("Hello World", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_FULLSCREEN_DESKTOP);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	if(window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	if (renderer == NULL) {
		printf("Failed to set screen. SDL error: %s\n", SDL_GetError());
		return false;
	}

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (texture == NULL) {
		printf("Texture failed to initialize. SDL error: %s\n", SDL_GetError());
		return false;
	}

	if (TTF_Init() != 0) {
		printf("TTF could not load, %s\n", SDL_GetError());
		return false;
	}

   	font = TTF_OpenFont("fonts/FreeSans.ttf", 16);
	if (font == NULL) {
		printf("Failed to initialize font, Error: %s\n", SDL_GetError());
		return false;
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

	//Load texture pixel colors into a pixel array so calculations don't need to be done per frame
	for (int t = 0; t < NUM_TEXTURES; ++t)
		for (int x = 0; x < TEXTURE_SIZE; ++x)
			for (int y = 0; y < TEXTURE_SIZE; ++y)
				pixelArray[t][x][y] = getPixel(textureSource[t], x, y);

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

	//Exit SDL_ttf
	TTF_Quit();

	//Quit SDL subsystems
	SDL_Quit();
}