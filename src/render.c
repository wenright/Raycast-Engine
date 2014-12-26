#include "include/render.h"

void renderSky () {
	//Clear the screen
	drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB_SkyBlue);
}

void renderFloor () {
	if (posZ + MIDDLE_Y < 0)
		drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGB_Grey);
	else
		drawRect(0, MIDDLE_Y + posZ, SCREEN_WIDTH, MIDDLE_Y - posZ, RGB_Grey);
}

// ~85% of execution time spent here
void renderWalls () {
	//For each pixel on the x axis
	for (int x = 0; x < SCREEN_WIDTH; ++x) {
		double screenCoordinate = (x << 1) / (double)SCREEN_WIDTH - 1;
		double rayPosX = posX;
		double rayPosY = posY;
		double rayDirX = dirX + planeX * screenCoordinate;
		double rayDirY = dirY + planeY * screenCoordinate;

		//get X, Y coordinate of map by truncating current position
		int mapX = (int) rayPosX;
		int mapY = (int) rayPosY;

		//Distance from current pos to next x or y side
		double sideDistX;
		double sideDistY;

		//Length from one side to the other
		double deltaX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double wallDist;

		//Direction to step (+1 or -1)
		int stepX;
		int stepY;

		//north south, or east west?
		int nsWall = false;

		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (rayPosX - mapX) * deltaX;
		}
		else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - rayPosX) * deltaX;
		}

		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (rayPosY - mapY) * deltaY;
		}
		else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - rayPosY) * deltaY;
		}

		//DDA
		while (!worldMap[mapX][mapY]) {
			//Jump to next square
			if (sideDistX < sideDistY) {
				sideDistX += deltaX;
				mapX += stepX;
				nsWall = false;
			}
			else {
				sideDistY += deltaY;
				mapY += stepY;
				nsWall = true;
			}

			if (mapX > MAP_WIDTH || mapY > MAP_HEIGHT)
				return;
		}

		//Calculate distance to camera
		if (nsWall)
			wallDist = fabs ((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);
		else
			wallDist = fabs ((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);

		//Calculates height of wall to be drawn. Multiply by some value to create non-cube walls
		int wallHeight = abs ((int)(SCREEN_HEIGHT / wallDist));

		//Calculate lowest and heighest points to be drawn
		int start = -wallHeight / 2 + SCREEN_HEIGHT / 2;
		if (start < -posZ)
			start = -posZ;

		int end = wallHeight / 2 + SCREEN_HEIGHT / 2;
		if (end > SCREEN_HEIGHT - posZ)
			end = SCREEN_HEIGHT - posZ;

		#if !textured
			//Renders single colors
			Uint32 color;
			switch(worldMap[mapX][mapY]) {
				case 1: color = RGB_Red;	break;
				case 2:	color = RGB_Yellow;	break;
				case 3: color = RGB_Blue;	break;
				case 4: color = RGB_Green;	break;
				default:color = RGB_White;	break;
			}

			//Half the color of some sides, looks better
			if (nsWall)
				color = color / 2;

			//Draw vertical line
			int y1 = start + posZ;
			if (y1 < 0)
				y1 = 0;

			int y2 = end + posZ;
			if (y2 < 0)
				y2 = 0;

			drawLine (x, y1, y2, color);
		#else
			//Calculates how far along the wall this ray has hit (for use w/ texture)
			double wallX = 0.0;
			if (nsWall)
				wallX = rayPosX + ((mapY - rayPosY + ((1 - stepY) >> 1)) / rayDirY) * rayDirX;
			else
				wallX = rayPosY + ((mapX - rayPosX + ((1 - stepX) >> 1)) / rayDirX) * rayDirY;
			wallX -= floor(wallX);

			//Calculates x coordinate of texture
			int textureX = (int) (wallX * (double)TEXTURE_SIZE);
			if ((!nsWall && rayDirX > 0) || (nsWall && rayDirY < 0))
				textureX = TEXTURE_SIZE - textureX - 1;

			///Select texture from zero indexed array
			int textureIndex = worldMap[mapX][mapY] - 1;

			//Calculate brightness of this strip of pixels
			double brightness = wallDist / 2;

			//For all of the pixels in the Y direction
			for (int y = start; y < end; ++y) {
				//Uses integers to avoid floating point arithmetic
				int textureY = ((((y << 1) - SCREEN_HEIGHT + wallHeight) << TEXTURE_SIZE_BINARY) / wallHeight) >> 1;

				//Pick color from pixel array
				Uint32 color = pixelArray[textureIndex][textureX][textureY];

				//Seperate the colors
				int red = (color >> 16)	& 0x0FF;
				int green = (color >> 8)& 0x0FF;
				int blue = (color)		& 0x0FF;

				//Modify the colors
				if (brightness > 1) {
					red /= brightness;
					green /= brightness;
					blue /= brightness;
				}

				//Recombine the colors
				color = ((red & 0x0ff) << 16) | ((green & 0x0ff)<<8) | (blue & 0x0ff);

				//Draw the individual pixel. May be faster if a buffer is used
				drawPoint(x, y + posZ, color);
			}
		#endif
	}
}

void updateTexture () {
	SDL_UpdateTexture(texture, NULL, pixelBuffer, SCREEN_WIDTH * 4);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	drawFPSToRenderer();
	SDL_RenderPresent(renderer);
}