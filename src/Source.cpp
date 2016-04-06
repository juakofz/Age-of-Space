//Librería básica y de imagen
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

//#include "Vector2.h"
#include "Texture.h"
#include "Vector2.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Button.h"
#include "Menu.h"
#include "ViewPort.h"
#include "LWindow.h"
#include "Global.h"

//#include "Global.h"
/*//Tamaño de la ventana
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
//bool init();

//Frees media and shuts down SDL
//void close();*/

//The window we'll be rendering to
//SDL_Window* gWindow = NULL;

//The window renderer
//SDL_Renderer* gRenderer = NULL;

/*extern SDL_Renderer* gRenderer;

extern LWindow gWindow;

extern Texture gSceneTexture;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//Loads media
bool loadMedia();*/

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			bool size;
			ViewPort menu,barra;
			ViewPort juego;
			menu.Init(0,3*SCREEN_HEIGHT/4,SCREEN_WIDTH,SCREEN_HEIGHT/4, "menu.png");
			juego.Init(0,SCREEN_HEIGHT/10,SCREEN_WIDTH,3*SCREEN_HEIGHT/4, "asteroide.png");
			menu.SetRel(0,0.75,1,0.25);
			juego.SetRel(0,0.1,1,0.75);
			barra.Init(0,0,SCREEN_WIDTH, SCREEN_HEIGHT/10, "barra.png");
			barra.SetRel(0,0,1,0.1);
			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle window events
					size=gWindow.handleEvent( e );
					
				}

				//Only draw when not minimized
				if( !gWindow.isMinimized() )
				{
					//Clear screen
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );
					//Vector2 dim=gSceneTexture.getDim;
					//gSceneTexture.
					//Render text textures
					Vector2 WindowQuad;
					WindowQuad.x=gWindow.getWidth();
					WindowQuad.y=gWindow.getHeight();

					if(size)
					{
						menu.ActParam();
						juego.ActParam();
						barra.ActParam();
						printf("tamaño nuevo");
						//ajustar el tamaño a la ventana.					
						WindowQuad.x=gWindow.getWidth();
						WindowQuad.y=gWindow.getHeight();
						//gSceneTexture.render(gRenderer,&WindowQuad);
						size=false;
					}
					//Update screen				
					//gSceneTexture.render(gRenderer,&WindowQuad);
					menu.render();
					juego.render();
					barra.render();
					SDL_RenderPresent( gRenderer );
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
		//parte de mr juako
		/*//Nave		
		Ship ship;
		ship.tex.load("nave.png", gRenderer);
		ship.SetCen(15, 15);
		ship.stop();
		
		//Nave 2
		Ship ship2;
		ship2.tex.load("nave.png", gRenderer);
		ship2.SetCen(300, 15);
		ship.stop();
		

		//Muchas naves
		Ship naves[10][10];
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				naves[i][j].tex.load("nave1.png", gRenderer);
				naves[i][j].SetCen(50 + 40 * i, 50 + 40 * j);
				naves[i][j].stop();
			}
		}

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

				ship2.event(&e);
				ship2.render(gRenderer);

				//Eventos de muchas naves
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						naves[i][j].event(&e);
						naves[i][j].render(gRenderer);
					}
				}
			}
			//Movimiento
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					naves[i][j].move();
				}
			}

			ship.move();
			
			//Limpiar pantalla
			SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0xFF);
			SDL_RenderClear(gRenderer);

			//Renderizar nave
			ship.render(gRenderer);
			ship2.render(gRenderer);

			//Renderizar muchas naves
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					naves[i][j].render(gRenderer);
				}
			}

			//Actualizar pantalla
			SDL_RenderPresent(gRenderer);
			}*/
}

/*bool init()
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
}*/
