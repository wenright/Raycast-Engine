#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

	#include <SDL2/SDL.h>

	#define RGB_Yellow 16120320
	#define RGB_Green 64000
	#define RGB_Blue 2800
	#define RGB_Red 16386560
	#define RGB_White 16775930

	#define true 1
	#define false 0

	#define SCREEN_WIDTH 800
	#define SCREEN_HEIGHT 600

	#define MAP_WIDTH 24
	#define MAP_HEIGHT 24

	#define NUM_TEXTURES 4
	#define TEXTURE_SIZE 64

	//Whether or to use textures when rendering
	#define textured true

	//Creates a world map
	extern int worldMap[MAP_WIDTH][MAP_HEIGHT];

	//Player position
	extern double posX, posY;

	//Player movement direction vector
	extern int moveX, moveY;

	//Player vector variables
	extern double dirX, dirY, planeX, planeY;

	//Player movement speed
	extern double speed, rotateSpeed;

	//The window we'll be rendering to
	extern SDL_Window* window;

	//The surface contained by the window
	extern SDL_Surface* screen;

	//The image we will load and show on the screen
	extern SDL_Surface* textureSource[NUM_TEXTURES];

#endif