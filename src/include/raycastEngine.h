#ifndef RAYCASTENGINE_H_INCLUDED
#define RAYCASTENGINE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include "variables.h"
#include "init.h"
#include "input.h"
#include "draw.h"
#include "render.h"
#include "fps.h"
#include "mapgen.h"

int worldMap[MAP_WIDTH][MAP_HEIGHT];

//Initial player position
double posX = 22.5, posY = 12.5, posZ = 0;
//Player movement direction vector
int moveLeft = false, moveRight = false, moveFwd = false, moveBck = false;
//Player vector variables
double dirX = -1.0, dirY = 0.0, planeX = 0.0, planeY = 0.66;
//Player movement speed
double speed = 5.0, rotateSpeedX = 0.0045, rotateSpeedY = 1.5;

//The window we'll be rendering to
SDL_Window* window;

//The surface contained by the window
SDL_Renderer* renderer;

//The texture that we will be streaming pixels to
SDL_Texture* texture;

//The pixel array that is used as a buffer for the texture
Uint32 pixelBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

//The image we will load and show on the screen
SDL_Surface* textureSource[NUM_TEXTURES];

//Te array of pixels for each of the textures, so they don't have to be calcuated each frame
Uint32 pixelArray[NUM_TEXTURES][TEXTURE_SIZE][TEXTURE_SIZE];

#endif