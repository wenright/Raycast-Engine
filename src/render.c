#include "include/render.h"

void renderWalls () {
	//For each pixel on the x axis
	for (int x = 0; x < SCREEN_WIDTH; x++) {
		double screenCoordinate = 2 * x / (double)SCREEN_WIDTH - 1;
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

		//If a wall was hit
		int hit = false;

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
		while (!hit) {
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

			if (worldMap[mapX][mapY] > 0)
				hit = true;
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
		if (start < 0)	
			start = 0;

		int end = wallHeight / 2 + SCREEN_HEIGHT / 2;
		if (end >= SCREEN_HEIGHT)	
			end = SCREEN_HEIGHT - 1;

		if (!textured) {
			//Renders flat textures
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
			drawLine (screen, x, start, end, color);
		}
		else {
			//Calculates how far along the wall this ray has hit (for use w/ texture)
			double wallX = 0.0;
			if (nsWall)
				wallX = rayPosX + ((mapY - rayPosY + (1 - stepY) / 2) / rayDirY) * rayDirX;
			else
				wallX = rayPosY + ((mapX - rayPosX + (1 - stepX) / 2) / rayDirX) * rayDirY;
			wallX -= floor(wallX);

			//Calculates x coordinate of texture
			int textureX = (int) (wallX * (double)TEXTURE_SIZE);
			if ((!nsWall && rayDirX > 0) || (nsWall && rayDirY < 0))
				textureX = TEXTURE_SIZE - textureX - 1;

			///Select texture from zero indexed array
			int textureIndex = worldMap[mapX][mapY] - 1;

			//Lock surface so we may view it
			SDL_LockSurface(textureSource[textureIndex]);

			//Retrieve array of pixels from the texture that we are using
			Uint32 *index = (Uint32 *)textureSource[textureIndex]->pixels;

			//For all of the pixels in the Y direction
			//TODO: one line of pixels is cut off from bottom of screen. end + 1 causes artifact 
			//	on line of pixels on bottom of texture
			for (int y = start; y < end; y++) {
				//Uses integers to avoid floating point arithmetic
				int textureY = (((y * 256 - SCREEN_HEIGHT * 128 + wallHeight * 128) 
					* TEXTURE_SIZE) / wallHeight) / 256;

				//Pick color from pixel array
				Uint32 color = getPixel(textureSource[textureIndex], textureX, textureY);

				//Darken colors on one side of wall, gives a lit effect
				if (nsWall)
					color = (color >> 1) & 8355711;

				//Draw the individual pixel. May be faster if a buffer is used
				drawPoint(screen, x, y, color);
			}

			//Unlock the previously locked fram
			SDL_UnlockSurface(textureSource[textureIndex]);
		}
	}
}