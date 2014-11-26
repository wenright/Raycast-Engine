#include "include/input.h"

int handleInput () {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ){
					case SDLK_LEFT:
					case 'a':
						moveLeft = true;
						break;
					case 'd':
					case SDLK_RIGHT:
						moveRight = true;
						break;
					case 'w':
					case SDLK_UP:
						moveFwd = true;
						break;
					case 's':
					case SDLK_DOWN:
						moveBck = true;
						break;
					default:
						break;
				}
				break;
			case SDL_KEYUP:
				switch( event.key.keysym.sym ){
					case SDLK_LEFT:
					case 'a':
						moveLeft = false;
						break;
					case 'd':
					case SDLK_RIGHT:
						moveRight = false;
						break;
					case 'w':
					case SDLK_UP:
						moveFwd = false;
						break;
					case 's':
					case SDLK_DOWN:
						moveBck = false;
						break;
					case SDLK_ESCAPE:
						return false;
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEMOTION:
				if (event.motion.xrel) {
					double newRotateSpeed = (double)event.motion.xrel * -rotateSpeedX;
					double oldDirX = dirX;
					dirX = dirX * cos(newRotateSpeed) - dirY * sin(newRotateSpeed);
					dirY = oldDirX * sin(newRotateSpeed) + dirY * cos(newRotateSpeed);
					double oldPlaneX = planeX;
					planeX = planeX * cos(newRotateSpeed) - planeY * sin(newRotateSpeed);
					planeY = oldPlaneX * sin(newRotateSpeed) + planeY * cos(newRotateSpeed);
				}

				if ((event.motion.yrel > 0 && posZ > -750) || (event.motion.yrel < 0 && posZ < 750))
					posZ += event.motion.yrel * -rotateSpeedY;
				
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
	if (moveFwd) {
		double moveStepX = dirX * deltaTime * speed;
		double moveStepY = dirY * deltaTime * speed;

		if (!worldMap[(int)(posX + moveStepX)][(int)posY])
			posX += moveStepX;
		if (!worldMap[(int)(posX)][(int)(posY + moveStepY)])
			posY += moveStepY;
	}
	if (moveBck) {
		double moveStepX = -dirX * deltaTime * speed;
		double moveStepY = -dirY * deltaTime * speed;

		if (!worldMap[(int)(posX + moveStepX)][(int)posY])
			posX += moveStepX;
		if (!worldMap[(int)(posX)][(int)(posY + moveStepY)])
			posY += moveStepY;
	}
	//Strafe
	if (moveRight) {
		//Find perp. vector by switching x and y, and negating one
		double moveStepX = dirY * deltaTime * speed;
		double moveStepY = -dirX * deltaTime * speed;

		if (!worldMap[(int)(posX + moveStepX)][(int)posY])
			posX += moveStepX;
		if (!worldMap[(int)(posX)][(int)(posY + moveStepY)])
			posY += moveStepY;
	}
	if (moveLeft) {
		double moveStepX = -dirY * deltaTime * speed;
		double moveStepY = dirX * deltaTime * speed;

		if (!worldMap[(int)(posX + moveStepX)][(int)posY])
			posX += moveStepX;
		if (!worldMap[(int)(posX)][(int)(posY + moveStepY)])
			posY += moveStepY;
	}
}