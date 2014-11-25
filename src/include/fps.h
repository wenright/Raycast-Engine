#ifndef FPS_H_INCLUDED
#define FPS_H_INCLUDED

#include <SDL2/SDL.h>
#include <time.h>
#include "variables.h"

//Frames per second to be capped at
#define framerate = 60;

double calcFPS ();

#endif