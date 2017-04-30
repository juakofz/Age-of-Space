//SDL libraries
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//C++ libraries
#include <stdio.h>
#include <string>
#include <sstream>
#include <conio.h>

//Global variables and functions
#include "Global.h"

//Classes
#include "Timer.h"
#include "Texture.h"
#include "Vector2.h"
#include "Window.h"
#include "Game.h"

//#include "Ship.h"
//#include "Asteroid.h"
//#include "Button.h"
//#include "Menu.h"
//#include "ViewPort.h"
//#include "Game.h"
//#include "Mouse.h"
//#include "Coordinator.h"


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

		//Coordinator main_coord; //Game state cordinator
		//main_coord.initGame();
		
		Game game;
		game.cargarTexturas();
		game.cargarTexturas();
		game.InitViewPorts();
		game.initjuego();
		game.initMenu();

		//While application is running
		while(!f_quit)
		{
				
			cap_timer.start(); //FPS cap

			//main_coord.mainEvent();//Non queue events
			game.main_event();

			//Handle events on queue
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT) f_quit = true; //quit via window event
				//if(main_coord.event(&e)) f_quit = true; //quit via game event
				game.event(&e);
				f_size = g_Window.handleEvent(e); //Resize event
			}

			//Only draw when not minimized
			if( !g_Window.isMinimized() )
			{
				//Clear screen
				SDL_SetRenderDrawColor( g_Renderer, 0xFF, 0x00, 0x00, 0xFF );
				SDL_RenderClear( g_Renderer );

				//Cálculo de fps
				float avgFPS = countedFrames / (fps_timer.getTicks() / 1000.f);
				if (avgFPS > 2000000) avgFPS = 0;
				if (fps_timer.getTicks() > 2000)
				{
					countedFrames = 0;
					fps_timer.start();
				}

				////FPS in screen display
				//SDL_Color fps_color = { 200,200,0 }; //Bright yellow
				//gTextTexture.loadText("FPS", 20, fps_color);
				//
					
				//std::cout << "FPS: " << avgFPS << '\r'; //FPS console display

				//Update window parameters if necessary
				if(f_size)
				{
					//main_coord.actViewports();//update viewports
					game.UpdateViewPorts();
					//WindowQuad = gWindow.getSize(); //update screen sizes
					f_size = false; //reset flag
				}

				game.RenderViewPorts();
				SDL_RenderPresent(g_Renderer); //update game render

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

	//Free resources and close SDL
	close();
	return 0;
}