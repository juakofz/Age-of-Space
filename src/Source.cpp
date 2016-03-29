//Librería básica y de imagen
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Vector2.h"
#include "Texture.h"
#include "Ship.h"

//Tamaño de la ventana
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

int main(int argc, char* args[])
{
	//Iniciar SDL y crear ventana
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Flag principal
		bool quit = false;

		//Manejo de eventos
		SDL_Event e;

		//Nave
		Ship ship;
		ship.SetPos(100, 100);

		//Bucle principal
		while (!quit)
		{
			//Manejo de eventos
			while (SDL_PollEvent(&e) != 0)
			{
				//Cerrar?
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				
				//Eventos de la nave
				ship.event(&e);
				ship.render(gRenderer);
			}

			//Limpiar pantalla
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			//Renderizar nave
			ship.tex.load("nave.png", gRenderer);
			ship.render(gRenderer);

			//Actualizar pantalla
			SDL_RenderPresent(gRenderer);
			}
		}

	//Liberar recursos y cerrar SDL
	close();

	return 0;
}

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
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

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
