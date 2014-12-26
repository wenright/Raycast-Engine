#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <SDL2/SDL.h>
#include "draw.h"
#include "variables.h"
#include "fps.h"

//Renders sky by writing a single color over the whole screen
void renderSky ();

//Renders the floor (solid color only for now)
void renderFloor ();

//Renders the world's walls
void renderWalls ();

//Updates the texture by applying it to the screen
void updateTexture ();

#endif