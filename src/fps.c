#include "include/fps.h"

//Current and previous frame time
double curTime = 0, prevTime = 0;

double calcFPS () {
	prevTime = curTime;
	curTime = clock();
	double deltaTime = (curTime - prevTime) / CLOCKS_PER_SEC;
	//printf("FPS:%f\n", 1.0 / deltaTime);

	return deltaTime;
}