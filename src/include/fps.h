#ifndef FPS_H_INCLUDED
#define FPS_H_INCLUDED

#include <time.h>
#include "variables.h"

//Frames per second to be capped at
#define framerate = 60;

//Surface for text to be rendered to
SDL_Surface* text;

//Font to be used
TTF_Font* font;

double calcFPS ();

void drawFPSToRenderer ();

#endif