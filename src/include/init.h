#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "variables.h"

//Starts up SDL and creates window
int init_SDL();

//Loads media
int loadMedia();

//Frees media and shuts down SDL
void close_SDL();

#endif