#include "include/fps.h"

//Current and previous frame time
double curTime = 0, prevTime = 0;

double calcFPS () {
	prevTime = curTime;
	curTime = clock();
	double deltaTime = (curTime - prevTime) / CLOCKS_PER_SEC;
	//Only update the FPS every couple of frames
	if (!(rand() % 10)) {
		char* fps = malloc(2);
		sprintf(fps, "%.0f", 1.0 / deltaTime);
		SDL_Color c = {255, 255, 255};
		text = TTF_RenderText_Solid (font, fps, c);
		free(fps);
	}

	//Apply FPS text to screen
	SDL_BlitSurface(text, NULL, screen, NULL);
	SDL_UpdateWindowSurface (window);

	return deltaTime;
}