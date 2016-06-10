#include "Game.h"
#include <typeinfo>

Game::Game(void)
{
}


Game::~Game(void)
{
}

void Game::event(SDL_Event* e)
{
	
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
		numviewport = 1;
	}

	//Game viewport (juego)
	if(my > barra.getHeight() && my < menu.getY())
	{
		juego.Set();
		//Game selection events
		eventjuego(e);

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
		numviewport = 3;
	}

	//Menu area
	if(my >= juego.getHeight())
	{
		menu.Set();
		eventMenu(e);
		//Absolute
		mouse.setPos(mx, my);
		//Relative
		mouse.setR_pos(menu.relatxy(mx, my).x, menu.relatxy(mx, my).y);

		mouse.update(e, false);
		numviewport = 2;
	}		
}

void Game::cargarTexturas()
{
	tex[0].load("img/Nave1.png");
	tex[1].load("img/asteroide.png");
	tex[2].load("img/edificio.png");
	tex[3].load("img/markerW.png");
	tex[4].load("img/markerW.png");
	tex[5].load("img/Cursor.png");
	tex[6].load("img/Background.jpg");
	tex[7].load("img/grid2.png");

	tex[3].setColor(255, 100, 0);
	tex[4].setColor(0, 255, 0);


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

	//juego
	zonas[JUEGO]->initViewport(0,SCREEN_HEIGHT/10,SCREEN_WIDTH,SCREEN_HEIGHT*0.65, "");
	zonas[JUEGO]->SetRel(0,0.1,1,0.65);

	//menus
	zonas[MENU]->initViewport(0,3*SCREEN_HEIGHT/4,SCREEN_WIDTH,SCREEN_HEIGHT/4, "img/menu.png");
	zonas[MENU]->SetRel(0,0.75,1,0.25);


	//barra
	zonas[BARRA]->initViewport(0,0,SCREEN_WIDTH, SCREEN_HEIGHT/10, "img/barra.png");
	zonas[BARRA]->SetRel(0,0,1,0.1);
	
	//pantalla inicial
	zonas[TOTAL]->initViewport(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, "img/space2.png");
	zonas[TOTAL]->SetRel(0,0,1,1);

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
	zonas[MENU]->render();
	zonas[JUEGO]->render();
	renderJuego();
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

	//Mapa
	map.setSize(3000, 3000);
	map.setBg(tex + 6);
	map.setGrid(tex + 7);

	//Camara
	cam.setCen(map.getSize().x / 2, map.getSize().y / 2);

	//inicializacion asteroide
	ast.SetTex(tex+1);
	ast.setMarker(&(tex[4]));

	ast.SetCen(50,50);	
	ast.setSize(70);




	//inicializacion nave
	for(int i=0;i<60;i++)
	{
	
	ship[i].SetTex(tex);
	ship[i].setSize(60);
	ship[i].setMarker(&(tex[3]));
	ship[i].SetCen(15*i, 200);
	ship[i].stop();
	}

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

	prueba1.SetTex(tex);
	prueba1.setSize(60);
	prueba1.setMarker(&(tex[3]));
	prueba1.SetCen(1500, 1500);
	prueba1.stop();

	std::stringstream recursos[2];
	jugador.getRecursos(recursos);
	barra.setRecursos(recursos);
}

void Game::renderJuego()
{
	//viewport de juego
	juego.Set();
	
	//Mapa
	map.renderBg(cam);
	map.renderGrid(cam);

	//Movimiento de naves y renderizado
	for (int i = 0;i < 60;i++)
	{	
		ship[i].move();
		if (cam.isVisible(ship[i].GetCen(), 20))
		{
			ship[i].render(cam);
		}
	}
	//prueba1.move();
		if (cam.isVisible(prueba1.GetCen(), 20))
		{
			prueba1.render(cam);
		}
	if (cam.isVisible(ast.GetCen(), 20))
		{
			ast.render(cam);
		}
	asteroides.render(cam);
	naves.render(cam);
	objetos_prueba.render(cam);
	proyectiles.render(cam);


	/*//movemos la nave y acualizamos
	for(int i=0;i<60;i++)
	{
		ship[i].render(gRenderer, cam);
	}*/
	//mouse.render(gRenderer);
	if(ast.getSel()) 
	{
			renderMenu();
			int type=ast.getType();
	}
	if(asteroides.getSel()) renderMenu();
	juego.Set();
	
}



void Game::setNombre(std::string nombre)
{
	//nombrejugador=nombre;
	jugador.setName(nombre);
	barra.SetName(jugador.getName());
}

void Game::eventjuego(SDL_Event* e)
{
	//eventos de los elementos del juego
	ast.event(e, mouse.getMrect(), mouse.getMpos());
	for(int i=0;i<60;i++)
	{
	ship[i].event(e, mouse.getMrect(), mouse.getMpos());
//	ship[i].render(gRenderer);
	}
	prueba1.event(e, mouse.getMrect(), mouse.getMpos());
	/*if(ast.getSel()) renderMenu();
	juego.Set();*/
	asteroides.event(e, mouse.getMrect(), mouse.getMpos());
	//naves.event(e, mouse.getMrect(), mouse.getMpos());
	switch(naves.event(e, mouse.getMrect(), mouse.getMpos()))
	{
		case 1:
		{
			int i=0, j=0;
			do{
				
				if(naves.getSel(i))
				{
				
				Proyectil* aux = new Proyectil;
				aux->SetTex(tex+2);
				aux->setSize(20);
				//Vector2 aux_cen = naves.getCen(naves.getSel()-1);

				aux->SetCen(naves.getCen(i).x, naves.getCen(i).y);
				aux->moveTo(mouse.getMpos().x, mouse.getMpos().y);
				
				proyectiles.agregar(aux);
				j++;
				}
				i++;
			}while(naves.getSels()>j);
			
		}
	}
	proyectiles.event(e, mouse.getMrect(), mouse.getMpos());
	//proyectiles.impacto(naves);
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
		case 1:
			{
			static int i=0;
			Asteroid* aux = new Asteroid; 	
			aux->SetTex(tex+1);
			aux->setMarker(&(tex[4]));
			aux->SetCen(50*i++, 100);  
			aux->setSize(70);

			asteroides.agregar(aux);
			break;			
			}
		case 3:
			do{
			asteroides.eliminarAsteroide(asteroides.getSel()-1);
			}while(asteroides.getSel());
			break;
		case 4:
			cout<<"cerrar"<<endl;
			break;
	}
	//printf("dentro del menu");
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

void Game::initBarra()
{
	barra.SetName(jugador.getName());

	std::stringstream recursos[2];
	jugador.getRecursos(recursos);
	barra.setRecursos(recursos);
}

void Game::renderBarra()
{
	//viewport de menu
//	barra.Set();

	//renderizamos el menu
//	menubarra.render();
	barra.render();

}

void Game::eventBarra(SDL_Event* e)
{
	//eventos de la barra
	barra.event(e, barra.relatxy());

}

/*characts* Game::chooseElement(int type)
{
	characts datos;
	switch (type)
	{
	case 1:
		datos.*/