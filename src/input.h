#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

	#include <SDL2/SDL.h>
	#include "variables.h"

	#define MIDDLE_X SCREEN_WIDTH / 2
	#define MIDDLE_Y SCREEN_HEIGHT / 2

	//Handles player input, returns false if player has requested quit
	int handleInput();

	//Move the player based on values moveX and moveY
	void movePlayer(double deltaTime);

#endif