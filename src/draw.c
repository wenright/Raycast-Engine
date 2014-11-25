#include "draw.h"

void drawPoint (SDL_Surface* screen, Uint32 x, Uint32 y, Uint32 color) {
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = 1;
	r.h = 1;
	SDL_FillRect(screen, &r, color);
}

void drawLine (SDL_Surface* screen, Uint32 x, Uint32 y1, Uint32 y2, Uint32 color) {
	SDL_Rect r;
	r.x = x;
	r.y = y1;
	r.w = 1;
	r.h = y2 - y1;
	SDL_FillRect(screen, &r, color);
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