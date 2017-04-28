//SDL libraries
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//C++ libraries
#include <stdio.h>
#include <string>
#include <sstream>
#include <conio.h>

//Classes
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

//Global variables and functions
#include "Global.h"

using namespace std;

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if( !init() )
	{
		cout << "Failed to initialize SDL! Press any key to exit";
		_getch();
		close();
		return -1;
	}
	else
	{
		//Start screen
		SDL_Color text_color = { 0,200,0 }; //Bright green
		if( !gTextTexture.loadText("WELCOME TO AGE OF SPACE", 28, text_color) )
		{
			cout << "Failed to load media!\n" << endl;
		}
		else
		{	
			//Vsync: 0 =  disabled, 1 = Strict, -1 =  Adaptative
			SDL_GL_SetSwapInterval(0);
			
			bool f_quit = false; //main loop flag
			bool f_total = true; //start screen flag
			bool f_size = false; //screen resize flag
			
			srand(SDL_GetTicks()); //Random seed

			//FPS variables
			Timer fps_timer, cap_timer;
			int countedFrames = 0;
			fps_timer.start();

			SDL_Event e; //Event handler

			//Player name
			/*SDL_Color textColor = { 0, 0, 255};
			int tamaño = 28;
			std::string inputText = "Jugador";
			gInputTextTexture.loadText(inputText.c_str(), tamaño, textColor);
			*/

			Coordinator main_coord; //Game state cordinator
			main_coord.initGame();

			//While application is running
			while(!f_quit)
			{
				
				cap_timer.start(); //FPS cap

				main_coord.mainEvent();//Non queue events

				//Handle events on queue
				while(SDL_PollEvent(&e) != 0)
				{
					if(e.type == SDL_QUIT) f_quit = true; //quit via window event
					if(main_coord.event(&e)) f_quit = true; //quit via game event

					f_size = gWindow.handleEvent(e); //Resize event
					
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
					if (avgFPS > 2000000) avgFPS = 0;
					if (fps_timer.getTicks() > 2000)
					{
						countedFrames = 0;
						fps_timer.start();
					}

					////FPS display
					//SDL_Color fps_color = { 200,200,0 }; //Bright yellow
					//gTextTexture.loadText("FPS", 20, fps_color);
					//
					
					//std::cout<< "FPS: " << avgFPS << '\r';

					//Update window parameters if necessary
					if(f_size)
					{
						main_coord.actViewports();//update viewports
						WindowQuad = gWindow.getSize(); //update screen sizes
						f_size = false; //reset flag
					}

					main_coord.render(); //update game render
					SDL_RenderPresent(gRenderer);

					//FPS update
					++countedFrames;
					int frameTicks = cap_timer.getTicks();
					if (frameTicks < SCREEN_TICKS_PER_FRAME) //If frame finished early (cap)
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
	return 0;
}