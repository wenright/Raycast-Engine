#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define RGB_Yellow 16120320
#define RGB_Green 64000
#define RGB_Blue 2800
#define RGB_SkyBlue 11517695
#define RGB_Red 16386560
#define RGB_White 16775930
#define RGB_Grey 7895160

#define true 1
#define false 0

#define maxFPS 60
#define maxTicks 1000 / maxFPS

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 400

#define MIDDLE_X SCREEN_WIDTH / 2
#define MIDDLE_Y SCREEN_HEIGHT / 2

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

#define NUM_TEXTURES 4
#define TEXTURE_SIZE 64
#define TEXTURE_SIZE_BINARY (int)log2(TEXTURE_SIZE)

//Whether or to use textures when rendering
#define textured true

//Creates a world map
extern int worldMap[MAP_WIDTH][MAP_HEIGHT];

//Player position
extern double posX, posY, posZ;

//Player movement direction vector
extern int moveLeft, moveRight, moveFwd, moveBck;

//Player vector variables
extern double dirX, dirY, planeX, planeY;

//Player movement speed
extern double speed, rotateSpeedX, rotateSpeedY;

//The window we'll be rendering to
extern SDL_Window* window;

//The surface contained by the window
extern SDL_Renderer* renderer;

//The texture that we will be streaming pixels to
extern SDL_Texture* texture;

//The pixel array that is used as a buffer for the texture
extern Uint32 pixelBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

//The image we will load and show on the screen
extern SDL_Surface* textureSource[NUM_TEXTURES];

//The array of pixels for each of the textures, so they don't have to be calcuated each frame
extern Uint32 pixelArray[NUM_TEXTURES][TEXTURE_SIZE][TEXTURE_SIZE];

//Font used for FPS Debug
extern TTF_Font* font;

//Surface that font will be rendered onto
extern SDL_Surface* text;

#endif