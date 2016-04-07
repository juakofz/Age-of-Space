//Librería básica y de imagen
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

//#include "Vector2.h"
#include <SDL_ttf.h>
#include "Texture.h"
#include "Vector2.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Button.h"
#include "Menu.h"
#include "ViewPort.h"
#include "LWindow.h"
#include "Global.h"
#include "EnteSupremo.h"



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
		if( !loadText() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;
			bool total = true;
			//Event handler
			SDL_Event e;
			bool size;
			EnteSupremo yo;


			yo.InitViewPorts();
			yo.initjuego();

			//ast.render();
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

					if(total) 
					{
						yo.RenderTotal();
					
						size=gWindow.handleEvent( e );
						if( e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_RIGHT) total=false;
					}

					else
					{
						yo.RenderViewPorts();
						//Handle window events
						size=gWindow.handleEvent( e );
						yo.setViewPort(&e);
						yo.renderJuego();
						//if (e.type == SDL_MOUSEBUTTONDOWN)
					}
					
				}

				//Only draw when not minimized
				if( !gWindow.isMinimized() )
				{
					//Clear screen
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );

					//Render text textures
					Vector2 WindowQuad;
					WindowQuad.x=gWindow.getWidth();
					WindowQuad.y=gWindow.getHeight();

					if(size)
					{
					
						yo.ActViewPorts();

						//printf("tamaño nuevo");
						//ajustar el tamaño a la ventana.					
						WindowQuad.x=gWindow.getWidth();
						WindowQuad.y=gWindow.getHeight();
	
						size=false;
					}
					//Update screen		
					if(total)
					{
						yo.RenderTotal();
						gTextTexture.render( gRenderer, 0.1*gWindow.getWidth(), 0.4*gWindow.getHeight());

					}
					else
					{
							yo.RenderViewPorts();
							yo.renderJuego();
					}
					SDL_RenderPresent( gRenderer );
				}
			}
		}
	}

	//Free resources and close SDL
	close();
	//system("PAUSE");
	return 0;
}