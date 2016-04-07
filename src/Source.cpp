//Versión
#define VERSION_NUM "P 0.3"

//Librería básica y de imagen
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Vector2.h"
#include "Texture.h"
#include "Ship.h"
#include "mouse.h"
#include "Timer.h"


using namespace std;

//Tamaño de la ventana
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
//Límite FPS
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Mouse
Mouse mouse;
SDL_Rect mouse_selection;

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

		//FPS
		Timer fps_timer, cap_timer;
		int countedFrames = 0;
		fps_timer.start();

		//Manejo de eventos
		SDL_Event e;

		//Carga de texturas
		Texture tex[4];
		tex[0].load("nave1.png", gRenderer);
		tex[1].load("asteroide.png", gRenderer);
		tex[2].load("edificio.png", gRenderer);
		tex[3].load("markerW.png", gRenderer);

		tex[3].setColor(255, 100, 0);

		//Nave		
		Ship ship;
		ship.SetTex(tex);
		ship.setSize(15);
		ship.setMarker(&tex[3]);
		ship.SetCen(700, 500);
		ship.stop();
		
		//Muchas naves
		Ship naves[30][30];
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				naves[i][j].SetTex(tex);
				naves[i][j].setSize(17);
				naves[i][j].setMarker(&tex[3]);
				naves[i][j].SetCen(30 + 18 * i, 30 + 18 * j);
				naves[i][j].stop();
			}
		}

		//Bucle principal
		while (!quit)
		{

			//Límite FPS
			cap_timer.start();

			//Manejo de eventos
			while (SDL_PollEvent(&e) != 0)
			{
				//Cerrar?
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}

				//Eventos ratón
				mouse.update(&e);
				mouse_selection = mouse.getSel();

				//Eventos de la nave
				ship.event(&e, mouse_selection);

				//Eventos de muchas naves
				for (int i = 0; i < 30; i++) {
					for (int j = 0; j < 30; j++) {
						naves[i][j].event(&e, mouse_selection);
					}
				}
			}

			//Cálculo de fps
			float avgFPS = countedFrames / (fps_timer.getTicks() / 1000.f);
			if (avgFPS > 2000000)
			{
				avgFPS = 0;
			}
			if (fps_timer.getTicks() > 2000)
			{
				countedFrames = 0;
				fps_timer.start();
			}
			cout << "FPS: " << avgFPS << '\r';



			//Movimiento
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 30; j++) {
					naves[i][j].move();
				}
			}

			ship.move();
			
			//Limpiar pantalla
			SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0xFF);
			SDL_RenderClear(gRenderer);

			//Renderizar nave
			ship.render(gRenderer);

			//Renderizar ratón
			mouse.render(gRenderer);

			//Renderizar muchas naves
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 30; j++) {
					naves[i][j].render(gRenderer);
				}
			}

			//Actualizar pantalla
			SDL_RenderPresent(gRenderer);
			++countedFrames;

			//If frame finished early
			int frameTicks = cap_timer.getTicks();
			if (frameTicks < SCREEN_TICKS_PER_FRAME)
			{
				//Wait remaining time
				SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
			}

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
		gWindow = SDL_CreateWindow(VERSION_NUM, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
