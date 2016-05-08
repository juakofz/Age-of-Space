<<<<<<< HEAD
<<<<<<< HEAD
//Librerías de SDL y c++
=======
//Versión
#define VERSION_NUM "P 0.3"

//Librería básica y de imagen
>>>>>>> refs/remotes/origin/development
=======
//Librerías de SDL y c++
>>>>>>> refs/remotes/origin/development
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
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> refs/remotes/origin/development
#include "Asteroid.h"
#include "Button.h"
#include "Menu.h"
#include "ViewPort.h"
#include "LWindow.h"
#include "Game.h"
#include "Mouse.h"
#include "Timer.h"
<<<<<<< HEAD

//variables y funciones globales
#include "Global.h"
=======
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
>>>>>>> refs/remotes/origin/development

using namespace std;

//Mouse
Mouse mouse;
SDL_Rect mouse_selection;
=======

//variables y funciones globales
#include "Global.h"

using namespace std;
>>>>>>> refs/remotes/origin/development

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
<<<<<<< HEAD
<<<<<<< HEAD
		
		//Load media
		SDL_Color color = {0,255,0};

		//Texto de inicio del juego
		if( !gTextTexture.loadText("WELCOME TO AGE OF SPACE", 28, color) )
		{
			printf( "Failed to load media!\n" );
=======
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
>>>>>>> refs/remotes/origin/development
		}
		else
		{	

<<<<<<< HEAD
	//		SDL_GL_SetSwapInterval(0);
			//Main loop flag
			bool quit = false;

			//flag de pantalla de inicio
			bool total = true;


=======
		
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


>>>>>>> refs/remotes/origin/development
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
<<<<<<< HEAD
=======
		//Bucle principal
		while (!quit)
		{

			//Límite FPS
			cap_timer.start();

			//Manejo de eventos
			while (SDL_PollEvent(&e) != 0)
>>>>>>> refs/remotes/origin/development
=======
>>>>>>> refs/remotes/origin/development
			{
				//flag de cambio en el texto introducido
				bool renderText = false;


				//Límite FPS
				cap_timer.start();

<<<<<<< HEAD
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
<<<<<<< HEAD
=======
				//Non queue events
				game.main_event();

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
>>>>>>> refs/remotes/origin/development
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
<<<<<<< HEAD
					}
=======
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
>>>>>>> refs/remotes/origin/development

					//Si estamos en pantalla de inicio
					if(total) 
					{
									
						//eventos del cambio de pantalla
						size=gWindow.handleEvent( e );

<<<<<<< HEAD
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
					
=======
			//Renderizar nave
			ship.render(gRenderer);

			//Renderizar ratón
			mouse.render(gRenderer);

			//Renderizar muchas naves
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 30; j++) {
					naves[i][j].render(gRenderer);
>>>>>>> refs/remotes/origin/development
				}

<<<<<<< HEAD
=======
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

>>>>>>> refs/remotes/origin/development
				//Only draw when not minimized
				if( !gWindow.isMinimized() )
				{
					//Clear screen
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );
<<<<<<< HEAD
=======
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
>>>>>>> refs/remotes/origin/development
=======
>>>>>>> refs/remotes/origin/development

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

					
					std::cout<< "FPS: " << avgFPS << '\r';
					
<<<<<<< HEAD

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
							game.renderJuego();
						
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

<<<<<<< HEAD
=======
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
>>>>>>> refs/remotes/origin/development
=======

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

>>>>>>> refs/remotes/origin/development

				}
			}
		}
	}
<<<<<<< HEAD

	//Free resources and close SDL
	close();
	//system("PAUSE");
=======
	//system("PAUSE");
	//Free resources and close SDL
	close();
>>>>>>> refs/remotes/origin/development
	return 0;
}