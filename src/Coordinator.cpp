#include "Coordinator.h"


Coordinator::Coordinator(void)
{
	estado = INICIO;

	textColor.r = 0;
	textColor.g = 0;
	textColor.b = 255;

	tamaño = 28;
	inputText = "Jugador";
	gInputTextTexture.loadText(inputText.c_str(), tamaño, textColor);

	texto_cambio.loadText("NUEVA FASE", 28, textColor);
	texto_gameover.loadText("GAMEOVER", 46, textColor);
	texto_gameover2.loadText("UFF... ES DURO LA VERDAD", 46, textColor);
	texto_pause.loadText("PAUSE", 46, textColor);
	texto_pauseins.loadText("Pulse enter para ir al inicio", 28, textColor);
	texto_inicioins.loadText("Enter para empezar y esc para salir", 28, textColor);
	texto_win.loadText("ENHORABUENA, HAS SOBREVIVIDO", 46, textColor);

	fase = 0;

	for(int i = INICIO + 1; i < GAMEOVER; i++)
	{
		flags[i] = false;
	}

	flags[INICIO] = true;
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

bool Coordinator::event(SDL_Event *e)
{
	bool flag=false;
	switch (estado)
	{
		case INICIO:
			{
				
			//vamos a la pantalla de juego al pulsar enter
			if( e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN)
			{
					//game.reinitjuego(fase);
					estado = INTRO_FASE;
					flags[INTRO_FASE]=true;

			}

			if( e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
			{
				flag=true;
			}
			//función de entrada de texto y actualización del nombre
			renderText=textinput(&inputText, renderText, *e);
			game.setNombre(inputText);

			break;
			}

		case INTRO_FASE:
			{
			
				//tiempo_fase.start();
				//cout<<"fase nueva"<<endl;

				if(e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN)
					{
						estado=JUEGO;
						flags[JUEGO]=true;
				}
				break;
			}

		case JUEGO:
			{
				/*if(flags[JUEGO])
				{
					game.nuevafase(fase);
					tiempo_fase.start();
					tiempo_ataques.start();
					flags[JUEGO]=false;
				}*/
				if(e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_SPACE)
				{
						tiempo_fase.pause();
						tiempo_ataques.pause();
						flags[PAUSE]=true;
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
						flags[INTRO_FASE]=true;

						break;
					}
				case 2:
					{
						estado=GAMEOVER;
						flags[GAMEOVER]=true;
						break;
					}
				}
				break;
			}


		case PAUSE:
			{
				if(e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_SPACE)
				{
						tiempo_fase.unpause();
						tiempo_ataques.unpause();
						flags[JUEGO]=true;
						estado = JUEGO;
				}
				if(e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN)
				{
					flags[INICIO]=true;
					estado=INICIO;
				}

			break;
			}

		case WIN:
			{
				if(e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN)
				{
						flags[INICIO]=true;
						estado = INICIO;
				}
				break;
			}


		case GAMEOVER:
			{

				if(e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN)
				{
						flags[INICIO]=true;
						estado = INICIO;
				}
				break;
			}
	}
	return flag;
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
				if(flags[INICIO])
				{
					fase=0;
					game.reinitjuego();
					flags[INICIO]=false;
				}
			//pantalla de inicio
			game.RenderTotal();

			//textos del inicio
			gTextTexture.render( gRenderer, 0.1*gWindow.getWidth(), 0.4*gWindow.getHeight());
			Textrender(inputText, renderText, textColor, tamaño);
			gInputTextTexture.render( gRenderer, 0.1*gWindow.getWidth(), 0.6*gWindow.getHeight() );

			texto_inicioins.render(gRenderer, 0.1*gWindow.getWidth(), 0.8*gWindow.getHeight() );

			break;
			}

		case INTRO_FASE:
			{
				if(flags[INTRO_FASE])
				{
					fase++;

					stringstream nfase;
					nfase.str(" ");
					nfase<<fase;
					texto_nfase.loadText(nfase.str(), 40, textColor, 2);
					tiempo_fase.stop();
					tiempo_ataques.stop();
					flags[INTRO_FASE]=false;
				}
				game.RenderTotal();

				texto_cambio.render(gRenderer, 0.1*gWindow.getWidth(), 0.4*gWindow.getHeight());
				texto_nfase.render(gRenderer, 0.1*gWindow.getWidth(), 0.6*gWindow.getHeight());
				break;
			}

		case JUEGO:
			{
				if(flags[JUEGO])
				{
					game.nuevafase(fase);
					tiempo_fase.start();
					tiempo_ataques.start();
					flags[JUEGO]=false;
				}
				//renderizamos los viewports y los elementos del juego
				game.RenderViewPorts();
				
				if(tiempo_ataques.getSecs() > (10 - fase))
			
				{
					game.ataqueEnemigo();
					tiempo_ataques.start();
				}
				if(tiempo_fase.getSecs() > (30 + fase*10))
				{
					if(fase + 1 > 6) 
					{
						estado = WIN;
						flags[WIN] = true;
					}
					else
					{

						estado = INTRO_FASE;
						flags[INTRO_FASE] = true;
					}
				}
				break;	
			}

		case PAUSE:
			{
				game.RenderTotal();

				texto_pause.render(gRenderer, 0.1*gWindow.getWidth(), 0.4*gWindow.getHeight());
				texto_pauseins.render(gRenderer, 0.1*gWindow.getWidth(), 0.6*gWindow.getHeight());
				break;
			}

		case WIN:
			{
				if(flags[WIN])
				{
					flags[WIN]=false;
					fase=0;
				}

				game.RenderTotal();

				texto_win.render(gRenderer, 5, 0.4*gWindow.getHeight());
			}
		case GAMEOVER:
			{
				if(flags[GAMEOVER])
				{
						flags[GAMEOVER]=false;
						fase = 0;
				}


				game.RenderTotal();
				//texto_gameover.render(gRenderer, 0.3*gWindow.getWidth(), 0.4*gWindow.getHeight());
				texto_gameover2.render(gRenderer, (gWindow.getWidth() - texto_gameover2.getDim().x) / 2, 0.4*gWindow.getHeight());
				

				break;
			}
	}

}