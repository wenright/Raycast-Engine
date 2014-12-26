#include "include/draw.h"

void drawPoint (Uint32 x, Uint32 y, Uint32 color) {
	if (x > SCREEN_WIDTH | y > SCREEN_HEIGHT)	return;
	pixelBuffer[y][x] = color;
}

void drawLine (Uint32 x, Uint32 y1, Uint32 y2, Uint32 color) {
	for (int i = y1; i < y2; i++)
		pixelBuffer[i][x] = color;
}

void drawRect (Uint32 x, Uint32 y, Uint32 w, Uint32 h, Uint32 color) {
	for (int i = x; i < x + w; i++)
		for (int j = y; j < y + h; j++)
			pixelBuffer[j][i] = color;
}

Uint32 getPixel(SDL_Surface *surface, int x, int y) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
		case 1:
			return *p;
			break;
		case 2:
			return *(Uint16 *)p;
			break;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
			break;
		case 4:
			return *(Uint32 *)p;
			break;
		default:
			return 0;
	}
}