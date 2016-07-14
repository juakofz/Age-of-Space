#include "Game.h"
#include <typeinfo>

int Game::ataques=0;
bool Game::atacar=false;

Game::Game(void)
{
}


Game::~Game(void)
{
}

int Game::event(SDL_Event* e)
{
	int flag=false;
	//Reading absolute mouse state
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	
	//Top bar
	if (my <= barra.getHeight())
	{
		barra.Set();
		
		//Absolute
		mouse.setPos(mx, my);

		//Relative to viewport
		mouse.setR_pos(mx, my);

		mouse.update(e, false);
	}

	//Game viewport (juego)
	if(my > barra.getHeight() && my < menu.getY())
	{
		juego.Set();
		//Game selection events
		flag = eventjuego(e);

		//Lock mouse while selecting
		if (mouse.isActive())
		{
			//Upper limit
			if (my <= barra.getHeight())
			{
				//Absolute
				mouse.setPos(mx, barra.getHeight());
				//Relative
				mouse.setR_pos(mx, 0);
			}

			//Lower limit
			else if (my >= juego.getHeight() + menu.getHeight())
			{
				//Absolute
				mouse.setPos(mx, barra.getHeight() + juego.getHeight());
				//Relative
				mouse.setR_pos(mx, juego.getHeight());
			}

			else
			{
				//Absolute
				mouse.setPos(mx, my);
				//Relative
				mouse.setR_pos(mx, juego.relatxy(mx, my).y);
			}

		}
		//Not selecting
		else
		{
			//Absolute
			mouse.setPos(mx, my);
			//Relative
			mouse.setR_pos(mx, juego.relatxy(mx, my).y);
		}

		//Map
		mouse.setMpos(cam.getPos().x + mouse.getR_pos().x, cam.getPos().y + mouse.getR_pos().y);

		//Update mouse
		mouse.update(e);
	}


	if (my >= juego.getHeight())
	{
		//Menu area
		if (mx < menu.getWidth())
		{
			menu.Set();
			eventMenu(e);
			//Absolute
			mouse.setPos(mx, my);
			//Relative
			mouse.setR_pos(menu.relatxy(mx, my).x, menu.relatxy(mx, my).y);
			mouse.update(e, false);
		}
		else
		{
			minimapa.Set();
			eventMinimapa(e);
			//Absolute
			mouse.setPos(mx, my);
			//Relative
			mouse.setR_pos(minimapa.relatxy(mx, my).x, minimapa.relatxy(mx, my).y);
		}
	}
	return flag;
}

void Game::cargarTexturas()
{
	tex[0].load("img/Nave.png");
	tex[1].load("img/asteroide.png");
	tex[2].load("img/edificio.png");
	tex[3].load("img/markerW.png");
	tex[4].load("img/markerW.png");
	tex[5].load("img/Cursor1.png");
	tex[6].load("img/Background.png");
	tex[7].load("img/grid3.png");
	tex[8].load("img/Nave.png");
	tex[9].load("img/disparo.png");
	tex[10].load("img/disparo.png");

	tex[5].setColor(0, 255, 0); // Cursor Verde
	tex[0].setColor(30, 210, 240); //Nave cian
	tex[3].setColor(255, 100, 0); //Marcador naranja
	tex[4].setColor(0, 255, 0); //Marcador verde
	tex[8].setColor(210, 50, 50); //Nave roja
	tex[9].setColor(0, 255, 0); //Disparo verde

	texOpciones[0].load("img/edificio.png");
	texOpciones[1].load("img/markerW.png");
	texOpciones[2].load("img/Nave1.png");
	texOpciones[3].load("img/atras.png");
	texOpciones[4].load("img/cerrar.png");
}

void Game::InitViewPorts()
{
	zonas[MENU]=&menu;
	zonas[BARRA]=&barra;
	zonas[TOTAL]=&total;
	zonas[JUEGO]=&juego;
	zonas[MINIMAPA]=&minimapa;

	//juego
	zonas[JUEGO]->initViewport(0,SCREEN_HEIGHT/10,SCREEN_WIDTH,SCREEN_HEIGHT*0.65, "");
	zonas[JUEGO]->SetRel(0,0.1,1,0.65);

	//menus
	zonas[MENU]->initViewport(0,3*SCREEN_HEIGHT/4,3*SCREEN_WIDTH/4,SCREEN_HEIGHT/4, "img/menu.png");
	zonas[MENU]->SetRel(0,0.75,0.75,0.25);


	//barra
	zonas[BARRA]->initViewport(0,0,SCREEN_WIDTH, SCREEN_HEIGHT/10, "img/barra.png");
	zonas[BARRA]->SetRel(0,0,1,0.1);
	
	//pantalla inicial
	zonas[TOTAL]->initViewport(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, "img/space2.png");
	zonas[TOTAL]->SetRel(0,0,1,1);

	//minimapa
	zonas[MINIMAPA]->initViewport(3*SCREEN_WIDTH/4,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/4, SCREEN_HEIGHT/4, "img/space2.png");
	zonas[MINIMAPA]->SetRel(0.75,0.75,0.25,0.25);

	//Actualizar tamaño de cámara
	cam.update(juego.getViewport());
}

void Game::ActViewPorts()
{
	//Actualizar viewports
	for(int i=0;i<NUM_VIEWPORTS;i++) zonas[i]->ActParam();

	//Actualizar tamaño de cámara
	cam.update(juego.getViewport());
}

void Game::RenderViewPorts()
{
	//viewports
	zonas[BARRA]->render();		
	renderBarra();
	zonas[MENU]->render();
	zonas[JUEGO]->render();
	zonas[MINIMAPA]->render();
	renderJuego();
	renderMinimapa();
	total.Set();
	mouse.render();

}

void Game::RenderTotal()
{
	zonas[TOTAL]->render();
	//mouse.render(gRenderer);
}

void Game::initjuego()
{
	//Inicialización del cursor
	mouse.setCursor(tex + 5);

	//Disparos
	Explosion::setTexture(tex + 10);
	GameObject::setTextures(tex + 9);

	//Mapa
	map.setSize(3000, 3000);
	map.setBg(tex + 6);
	map.setGrid(tex + 7);

	//Camara
	cam.setCen(map.getSize().x / 2, map.getSize().y / 2);

	//inicializacion asteroide
	ast.SetTex(tex+1);
	ast.setMarker(&(tex[4]));

	ast.SetCen(1500,1500);	
	ast.setSize(500);

	edificio.SetTex(tex+2);
	edificio.setMarker(tex+4);
	edificio.SetCen(1500, 1500);
	edificio.setSize(100);


	//inicializacion nave

	for(int i=0;i<20;i++)
	{
		Ship* aux = new Ship;
		aux->SetTex(tex);
		aux->setSize(60);
		aux->setMarker(&(tex[3]));
		aux->SetCen(150*i, 1500);
		aux->stop();

		naves.agregar(aux);
	}

	initBarra(1);
	/*std::stringstream recursos[2];
	jugador.getRecursos(recursos);
	barra.setRecursos(recursos);*/
}

void Game::reinitjuego()
{
	ataques = 1;

	ast.SetCen(1500,1500);	
	edificio.SetCen(1500, 1500);

	edificio.setVida(10);



	proyectiles.eliminarContenido();
	naves.eliminarContenido();

	for(int i=0;i<20;i++)
	{
		Ship* aux = new Ship;
		aux->SetTex(tex);
		aux->setSize(60);
		aux->setMarker(&(tex[3]));
		aux->SetCen(150*i, 1500);
		aux->stop();

		naves.agregar(aux);
	}

	initBarra(1);

}

void Game::nuevafase(int i)
{
	jugador.cambiarRecursos(0, 50);
	ataques=i;
	initBarra(i);
	naves.eliminarJugador(2);

}
void Game::renderJuego()
{
	//viewport de juego
	juego.Set();
	
	//Mapa
	map.renderBg(cam);
	map.renderGrid(cam);

	if (cam.isVisible(ast.GetCen(), 20))
		{
			ast.render(cam);
		}
	asteroides.render(cam);
	edificio.render(cam);
	naves.render(cam);
	objetos_prueba.render(cam);
	proyectiles.render(cam);

	if(edificio.getSel()) 
	{
			renderMenu();
			//int type=ast.getType();
	}
	
	//if(asteroides.getSel()) renderMenu();
	juego.Set();
}

void Game::setNombre(std::string nombre)
{
	//nombrejugador=nombre;
	jugador.setName(nombre);
	barra.SetName(jugador.getName());
}

int Game::eventjuego(SDL_Event* e)
{
	//eventos de los elementos del juego
	ast.event(e, mouse.getMrect(), mouse.getMpos());

	asteroides.event(e, mouse.getMrect(), mouse.getMpos());
	
	switch(naves.event(e, mouse.getMrect(), mouse.getMpos()))
	{
		case 1:
		{
			int i=0, j=0;
			do{
				
				if(naves.getSel(i))
				{

					Proyectil* aux = new Proyectil(naves.getPlayer(i));

					aux->SetTex(tex + 9);
					aux->setSize(25);
					//Vector2 aux_cen = naves.getCen(naves.getSel()-1);

					aux->SetCen(naves.getPointyEnd(i).x, naves.getPointyEnd(i).y);
					aux->moveTo(mouse.getMpos().x, mouse.getMpos().y);

					proyectiles.agregar(aux);
					j++;
				}
				i++;
			}while(naves.getSels()>j);
		}
	}

	proyectiles.event(e, mouse.getMrect(), mouse.getMpos());


	int oro=Interacciones::impactoListas(naves, proyectiles);
	if(oro)
	{
			jugador.cambiarRecursos(oro, 0);
			act_barra = true;
	}

	edificio.event(e, mouse.getMrect(), mouse.getMpos());
	if(Interacciones::impacto(edificio, proyectiles))
	{
		
		return 2;
		
	}
	else return 0;
	
	
		
}

void Game::main_event()
{
	mouse.scroll(cam, map);
}

void Game::initMenu()
{
	menu.setBotones(texOpciones);
	menu.setBotonQuad(40, 40);
}

void Game::renderMenu()
{
	//Abrimos el menu
	zonas[MENU]->Open();

}

void Game::eventMenu(SDL_Event* e)
{
	//eventos del menu
	switch (menu.event(e, menu.relatxy()))
	{
		case 2:
			{
				static int i=0;

				if(jugador.cambiarRecursos(-5, -1)) break;
				Ship* aux = new Ship(tex, 60, tex+3, Vector2(1500 + 15*i++, 1500), 1, true);				
				act_barra=true;
				naves.agregar(aux);

				break;			
			}

		case 3:
			do{
				naves.eliminarNave(naves.getSel()-1);
			} while(naves.getSel());
			break;
		
		case 4:
			//cout<<"cerrar"<<endl;
			break;
	}
}

void Game::initCaract()
{
	caract.setDim(Vector2(30,10), Vector2(40,40));
}

void Game::renderCaract()
{
	//viewport de menu
	menu.Set();

	//renderizamos el menu
	caract.render();
}

void Game::eventCaract(SDL_Event* e)
{
	//eventos del menu
	caract.event(e, menu.relatxy());
	//printf("dentro del menu");
}

void Game::initBarra(int fase)
{
	barra.SetName(jugador.getName());

	std::stringstream recursos[2];
	jugador.getRecursos(recursos);
	barra.setRecursos(recursos);

	barra.SetFase(fase);

}

void Game::renderBarra()
{
	//viewport de menu
//	barra.Set();
	if(act_barra)
	{
		std::stringstream recursos[2];
		jugador.getRecursos(recursos);
		barra.setRecursos(recursos);
	//	cout<<"actualizar"<<endl;
		act_barra=false;
	}
}

void Game::eventBarra(SDL_Event* e)
{
	//eventos de la barra
	barra.event(e, barra.relatxy());

}


//Minimapa guapo guapo
void Game::initMinimapa()
{
	//Lista de cositas?
}

void Game::renderMinimapa()
{
	minimapa.render();
	int margen = 10;
	int h = minimapa.getHeight();
	int w = minimapa.getWidth();

	//Map border
	SDL_Rect mapRect = {margen, margen, w - 2 * margen, h - 2 * margen };
	SDL_SetRenderDrawColor(gRenderer, 0, 128, 255, 255);
	SDL_RenderDrawRect(gRenderer, &mapRect);

	if (naves.getSize()) {
		for (int i = (naves.getSize() - 1); i >= 0; i--)
		{
			Vector2 p = naves.getCen(i);
			Vector2 rp;
			rp.x = (p.x / map.getSize().x) * (w - 2 * margen) + margen;
			rp.y = (p.y / map.getSize().y) * (h - 2 * margen) + margen;

			SDL_Rect fillRect = {rp.x, rp.y, 2, 2};
			switch (naves.getPlayer(i))
			{
			case 1:
				SDL_SetRenderDrawColor(gRenderer, 0, 255, 255, 0);
				break;
			case 2:
				SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
				break;
			default:
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
			}
			SDL_RenderFillRect(gRenderer, &fillRect);
		}
	}

	//Camera rect
	Vector2 c, rc, s, rs;
	
	c = cam.getPos();
	rc.x = (c.x / map.getSize().x) * (w - 2 * margen) + margen;
	rc.y = (c.y / map.getSize().y) * (h - 2 * margen) + margen;
	
	s = cam.getSize();

	rs.x = (s.x / map.getSize().x) * (w - 2 * margen);
	rs.y = (s.y / map.getSize().y) * (h - 2 * margen);

	SDL_Rect camRect = {rc.x, rc.y, rs.x, rs.y};
	SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 150);        
	SDL_RenderDrawRect( gRenderer, &camRect );

	//Renderizar minicositas

}

void Game::eventMinimapa(SDL_Event* e)
{
	int margen = 10;

	//Dentro en x
	if ((mouse.getR_pos().x >= margen) || (mouse.getR_pos().x >= minimapa.getWidth() + margen))
	{
		//Dentro en y
		if ((mouse.getR_pos().y >= margen) || (mouse.getR_pos().y >= minimapa.getHeight() + margen))
		{
			SDL_Point p;
			p.x = ((mouse.getR_pos().x - margen) * map.getSize().x) / (minimapa.getWidth() - 2 * margen);
			p.y = ((mouse.getR_pos().y - margen) * map.getSize().y) / (minimapa.getHeight() - 2 * margen);
			
			//Movimiento de cámara
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				cam.setCen(p.x, p.y);
			}

			//Movimiento de naves
			if (e->button.button == SDL_BUTTON_RIGHT)
			{
				naves.event(e, mouse.getMrect(), p);
			}
		}
	}
}

void Game::ataqueEnemigo()
{
	Vector2 centro;
	
	centro.x=  map.getSize().x / 2;
	centro.y = map.getSize().y / 2;
	int radio = ( ((centro.x<centro.y)?centro.x:centro.y) - 100 * ataques );
	float angulo = (2 * M_PI )/( ataques * 4);


	for(int j = 0; j < ataques*4; j++)
	{
		Ship* aux = new Ship(tex+8, 60, tex+3, Vector2(centro.x + radio * cos(angulo * j ), centro.y - radio * sin(angulo * j)), 2, false);
		naves.agregar(aux);
	}
	
	ataques++;
}