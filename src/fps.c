#include "include/fps.h"

//Current and previous frame time
double curTime = 0, prevTime = 0;

double calcFPS () {
	prevTime = curTime;
	curTime = clock();
	double deltaTime = (curTime - prevTime) / CLOCKS_PER_SEC;
	char* fps = malloc(2);
	sprintf(fps, "%.0f", 1.0 / deltaTime);
	SDL_Color c = {255, 255, 255};
	text = TTF_RenderText_Solid (font, fps, c);
	SDL_BlitSurface(text, NULL, screen, NULL);
	free(fps);

	return deltaTime;
}