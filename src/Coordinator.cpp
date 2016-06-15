#include "Coordinator.h"


Coordinator::Coordinator(void)
{
	estado=INICIO;

	textColor.r=0;
	textColor.g=0;
	textColor.b=255;

	tamaño = 28;
	inputText = "Jugador";
	gInputTextTexture.loadText(inputText.c_str(), tamaño, textColor);
}


Coordinator::~Coordinator(void)
{
}


void Coordinator::initGame()
{

	game.cargarTexturas();
	game.InitViewPorts();
	game.initjuego();

	game.initMenu();
}

void Coordinator::mainEvent()
{
	game.main_event();
}

void Coordinator::event(SDL_Event *e)
{
	switch (estado)
	{
		case INICIO:
			{
			
			//vamos a la pantalla de juego al pulsar enter
			if( e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN)
			{
					//game.reinitjuego(fase);
					game.reinitjuego();
					estado = INTRO_FASE;
			}

			//función de entrada de texto y actualización del nombre
			renderText=textinput(&inputText, renderText, *e);
			game.setNombre(inputText);

			break;
			}

		case INTRO_FASE:
			{
				//tiempo_fase.start();
				cout<<"fase nueva"<<endl;

				if(e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_SPACE)
					{
						game.nuevafase(fase);
						estado=JUEGO;
						tiempo_fase.start();
						tiempo_ataques.start();
				}

				break;
			}

		case JUEGO:
			{
				if(e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_SPACE)
				{
						tiempo_fase.pause();
						tiempo_ataques.pause();
						estado = PAUSE;
						
				}
				switch(game.event(e))
				{
				case 0:
					{
						break;
					}
				case 1:
					{
						estado=INTRO_FASE;
						fase++;

						break;
					}
				case 2:
					{
						estado=GAMEOVER;
						fase=0;

						break;
					}
				}

				if(tiempo_ataques.getSecs()>10)
				{
					game.ataqueEnemigo();
					tiempo_ataques.start();
				}
				if(tiempo_fase.getSecs()>100)
					{
						tiempo_fase.stop();
						tiempo_ataques.stop();
						estado= INTRO_FASE;
				}
				break;
			}


		case PAUSE:
			{
				cout<<"pause"<<endl;
				if(e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_SPACE)
				{
						tiempo_fase.unpause();
						tiempo_ataques.unpause();
						estado = JUEGO;
				}
				

			break;
			}

		case GAMEOVER:
			{
				cout<<"game over baby"<<endl;

				if(e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN) estado = INICIO;

				break;
			}
	}
}

void Coordinator::actViewports()
{
	game.ActViewPorts();
}

void Coordinator::render()
{
	switch (estado)
	{
		case INICIO:
			{
			//pantalla de inicio
			game.RenderTotal();

			//textos del inicio
			gTextTexture.render( gRenderer, 0.1*gWindow.getWidth(), 0.4*gWindow.getHeight());
			Textrender(inputText, renderText, textColor, tamaño);
			gInputTextTexture.render( gRenderer, 0.1*gWindow.getWidth(), 0.6*gWindow.getHeight() );

			break;
			}

		case INTRO_FASE:
			{

				

				break;
			}

		case JUEGO:
			{
				//renderizamos los viewports y los elementos del juego
				game.RenderViewPorts();
					break;	
			}

		case PAUSE:
			{
				cout<<"pause"<<endl;
				break;
			}
		case GAMEOVER:
			{

				

				break;
			}
	}

}