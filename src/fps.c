#include "fps.h"

//Current and previous frame time
double curTime = 0, prevTime = 0;

double calcFPS () {
	prevTime = curTime;
	curTime = clock();
	double deltaTime = (curTime - prevTime) / CLOCKS_PER_SEC;
	double framesPerSecond = 1.0 / deltaTime;
	//printf("FPS:%f\n", framesPerSecond);
	//if (framesPerSecond > framerate)
	//	SDL_Delay((framesPerSecond - framerate) / 1000.0);

	return deltaTime;
}