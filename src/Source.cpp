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

	//		SDL_GL_SetSwapInterval(0);
			//Main loop flag
			bool quit = false;

			//flag de pantalla de inicio
			bool total = true;


			//FPS
			Timer fps_timer, cap_timer;
			int countedFrames = 0;
			fps_timer.start();

			//Event handler
			SDL_Event e;

			//Nombre del jugador
			SDL_Color textColor = { 0, 0, 255};
			int tamaño = 28;
			std::string inputText = "Jugador";
			gInputTextTexture.loadText(inputText.c_str(), tamaño, textColor);

			//flag de cambio de tamaño de pantalla
			bool size=false;

			//game master
			Game game;

			//inicializamos los elementos del juego
			game.cargarTexturas();
			game.InitViewPorts();
			game.initjuego();

			game.initMenu();

			//While application is running
			while( !quit )
			{
				//flag de cambio en el texto introducido
				bool renderText = false;


				//Límite FPS
				cap_timer.start();

				//Non queue events
				game.main_event();

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Si estamos en pantalla de inicio

					if(total) 
					{
									
						//eventos del cambio de pantalla
						size=gWindow.handleEvent( e );

						//vamos a la pantalla de juego al pulsar enter
						if( e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_RETURN) total=false;

						//función de entrada de texto y actualización del nombre
						renderText=textinput(&inputText, renderText, e);
						game.setNombre(inputText);
					}

					//si estamos en la pantalla del juego
					else
					{

						game.event(&e);

						//Handle window events
						size=gWindow.handleEvent( e );

					}
					
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
						
						game.ActViewPorts();

						//ajustar el tamaño a la ventana.					
						WindowQuad.x=gWindow.getWidth();
						WindowQuad.y=gWindow.getHeight();
	
						size=false;
					}

					//Update screen		
					if(total)
					{
						//pantalla de inicio
						game.RenderTotal();

						//textos del inicio
						gTextTexture.render( gRenderer, 0.1*gWindow.getWidth(), 0.4*gWindow.getHeight());
						Textrender(inputText, renderText, textColor, tamaño);
						gInputTextTexture.render( gRenderer, 0.1*gWindow.getWidth(), 0.6*gWindow.getHeight() );
					}
					else
					{
							//renderizamos los viewports y los elementos del juego
							game.RenderViewPorts();
							//game.renderJuego();
						
					}

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
	//system("PAUSE");
	//Free resources and close SDL
	close();
	return 0;
}