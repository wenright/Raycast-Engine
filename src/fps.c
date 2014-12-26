#include "include/fps.h"

//Current and previous frame time
double curTime = 0, prevTime = 0;
int accumulatedFPS = 0, numFrames = 0;
char currentFPS[5];

double calcFPS () {
	prevTime = curTime;
	curTime = clock();
	double deltaTime = (curTime - prevTime) / CLOCKS_PER_SEC;
	int intFPS = 1 / deltaTime;
	accumulatedFPS += intFPS;
	numFrames++;

	if (numFrames > 120) {
		sprintf(currentFPS, "%d", accumulatedFPS / numFrames);
		numFrames = 0;
		accumulatedFPS = 0;
	}

	//Delay if we updated faster than maxFPS
	/*
	if (deltaTime < maxTicks) {
		SDL_Delay(maxTicks - deltaTime);
	}
	*/

	return deltaTime;
}

void drawFPSToRenderer () {
	SDL_Color White = {255, 255, 255};

	SDL_Surface* framerateTextSurface = TTF_RenderText_Solid(font, currentFPS, White);
	SDL_Texture* framerateTexture = SDL_CreateTextureFromSurface(renderer, framerateTextSurface);

	SDL_Rect r;
	r.x = 0; 
	r.y = 0;
	r.w = 50;
	r.h = 50;
	SDL_RenderCopy(renderer, framerateTexture, NULL, &r);
}