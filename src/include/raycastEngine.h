#ifndef RAYCASTENGINE_H_INCLUDED
#define RAYCASTENGINE_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdio.h>
#include "init.h"
#include "input.h"
#include "draw.h"
#include "render.h"
#include "fps.h"
#include "variables.h"
#include "mapgen.h"

int worldMap[MAP_WIDTH][MAP_HEIGHT];

//Initial player position
double posX = 22.5, posY = 12.5, posZ = 0;
//Player movement direction vector
int moveX = 0, moveY = 0;
//Player vector variables
double dirX = -1.0, dirY = 0.0, planeX = 0.0, planeY = 0.66;
//Player movement speed
double speed = 5.0, rotateSpeedX = 0.0045, rotateSpeedY = 1.5;

//The window we'll be rendering to
SDL_Window* window;

//The surface contained by the window
SDL_Surface* screen;

//The image we will load and show on the screen
SDL_Surface* textureSource[NUM_TEXTURES];

#endif