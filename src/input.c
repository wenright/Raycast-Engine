#include "include/input.h"

int handleInput () {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ){
					case SDLK_LEFT:
					case 'a':
						moveY = -1;
						break;
					case 'd':
					case SDLK_RIGHT:
						moveY = 1;
						break;
					case 'w':
					case SDLK_UP:
						moveX = 1;
						break;
					case 's':
					case SDLK_DOWN:
						moveX = -1;
						break;
					default:
						break;
				}
				break;
			case SDL_KEYUP:
				switch( event.key.keysym.sym ){
					case SDLK_LEFT:
					case 'a':
					case 'd':
					case SDLK_RIGHT:
						moveY = 0;
						break;
					case 'w':
					case SDLK_UP:
					case 's':
					case SDLK_DOWN:
						moveX = 0;
						break;
					case SDLK_ESCAPE:
						return false;
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEMOTION:;
				double newRotateSpeed = (double)event.motion.xrel * -rotateSpeed;
				double oldDirX = dirX;
				dirX = dirX * cos(newRotateSpeed) - dirY * sin(newRotateSpeed);
				dirY = oldDirX * sin(newRotateSpeed) + dirY * cos(newRotateSpeed);
				double oldPlaneX = planeX;
				planeX = planeX * cos(newRotateSpeed) - planeY * sin(newRotateSpeed);
				planeY = oldPlaneX * sin(newRotateSpeed) + planeY * cos(newRotateSpeed);
				SDL_WarpMouseInWindow(window, MIDDLE_X, MIDDLE_Y);
				break;
			case SDL_QUIT:
				return false;
				break;
			default:
				break;
		}
	}

	return true;
}

void movePlayer (double deltaTime) {
	//Move forward/backward
	if (moveX) {
		double moveStepX = moveX * dirX * deltaTime * speed;
		double moveStepY = moveX * dirY * deltaTime * speed;

		if (!worldMap[(int)(posX + moveStepX)][(int)posY])
			posX += moveStepX;
		if (!worldMap[(int)(posX)][(int)(posY + moveStepY)])
			posY += moveStepY;
	}
	//Strafe
	if (moveY) {
		//Find perp. vector by switching x and y, and negating one
		double moveStepX = moveY * dirY * deltaTime * speed;
		double moveStepY = moveY * -dirX * deltaTime * speed;

		if (!worldMap[(int)(posX + moveStepX)][(int)posY])
			posX += moveStepX;
		if (!worldMap[(int)(posX)][(int)(posY + moveStepY)])
			posY += moveStepY;
	}
}