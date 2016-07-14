//Librerías de SDL y c++
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

//Librerias de clases
#include "Texture.h"
#include "Vector2.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Button.h"
#include "Menu.h"
#include "ViewPort.h"
#include "LWindow.h"
#include "Game.h"
#include "Mouse.h"
#include "Timer.h"
#include "Coordinator.h"

//variables y funciones globales
#include "Global.h"

using namespace std;

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
		SDL_Color color = {0,255,0};

		//Texto de inicio del juego
		if( !gTextTexture.loadText("WELCOME TO AGE OF SPACE", 28, color) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//SDL_GL_SetSwapInterval(0);
			//Main loop flag
			bool quit = false;

			//flag de pantalla de inicio
			bool total = true;

			//Random seed
			srand(SDL_GetTicks());

			//FPS
			Timer fps_timer, cap_timer;
			int countedFrames = 0;
			fps_timer.start();

			//Event handler
			SDL_Event e;

			//Nombre del jugador
			/*SDL_Color textColor = { 0, 0, 255};
			int tamaño = 28;
			std::string inputText = "Jugador";
			gInputTextTexture.loadText(inputText.c_str(), tamaño, textColor);
			*/

			//flag de cambio de tamaño de pantalla
			bool size=false;

			//game master
			//Game game;
			Coordinator coordinador;

			//inicializamos los elementos del juego
			coordinador.initGame();



			//While application is running
			while( !quit )
			{

				//Límite FPS
				cap_timer.start();

				//Non queue events
				coordinador.mainEvent();

				//Handle events on queue
				while( SDL_PollEvent(&e) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}


					if(coordinador.event(&e)) quit=true;

					size=gWindow.handleEvent( e );
					
				}
				

				//Only draw when not minimized
				if( !gWindow.isMinimized() )
				{
					//Clear screen
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );

					//Tamaño de la ventana
					Vector2 WindowQuad;



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

					
					//std::cout<< "FPS: " << avgFPS << '\r';
					

					//si ha cambiado el tamaño de la ventana actualizamos los parámetros que dependen de ella.
					if(size)
					{
						
					//	game.ActViewPorts();
						coordinador.actViewports();

						//ajustar el tamaño a la ventana.					
						WindowQuad.x=gWindow.getWidth();
						WindowQuad.y=gWindow.getHeight();
	
						size=false;
					}

					coordinador.render();

					//actualizamos renderizado total
					SDL_RenderPresent( gRenderer );
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
		}
	}

	//Free resources and close SDL
	close();
	//system("PAUSE");
	return 0;
}