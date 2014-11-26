#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdio.h>
#include "variables.h"

//Draws a single point. There is probably a more efficient way of doing this.
void drawPoint (Uint32 x, Uint32 y, Uint32 color);

//Draws a line
void drawLine (Uint32 x, Uint32 y1, Uint32 y2, Uint32 color);

//Performs simple conversions to prepare a surface for accessing pixels
Uint32 getPixel(SDL_Surface* surface, int x, int y);

#endif