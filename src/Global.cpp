#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include "src\ViewPort.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
ViewPort barra, minimapa, menu, caract;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Age of Space - Prototype", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0x0FF, 0x0FF, 0x0FF, 0x0);

				//Viewpoints
				/*barra.SetParam(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/10);
				menu.SetParam(0, 3*SCREEN_HEIGHT/4, SCREEN_WIDTH/3, SCREEN_HEIGHT/4);
				caract.SetParam(SCREEN_WIDTH/3, 3*SCREEN_HEIGHT/4, SCREEN_WIDTH/3, SCREEN_HEIGHT/4);
				minimapa.SetParam(2*SCREEN_WIDTH/3, 3*SCREEN_HEIGHT/4, SCREEN_WIDTH/3, SCREEN_HEIGHT/4);*/

				barra.Init(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/10, "barra.png");
				menu.Init(0, 3*SCREEN_HEIGHT/4, SCREEN_WIDTH/3, SCREEN_HEIGHT/4, "menu.png");
				caract.Init(SCREEN_WIDTH/3, 3*SCREEN_HEIGHT/4, SCREEN_WIDTH/3, SCREEN_HEIGHT/4, "caracteristicas.png");
				minimapa.Init(2*SCREEN_WIDTH/3, 3*SCREEN_HEIGHT/4, SCREEN_WIDTH/3, SCREEN_HEIGHT/4, "minimapa2.png");

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void close()
{
	//Free loaded images
	//ship.tex.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
