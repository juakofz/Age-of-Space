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
	if(my > barra.getHeight() && my < menus.getY())
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
			else if (my >= juego.getHeight() + menus.getHeight())
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
		menus.Set();

		//Absolute
		mouse.setPos(mx, my);
		//Relative
		mouse.setR_pos(menus.relatxy(mx, my).x, menus.relatxy(mx, my).y);

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

	//juego
	juego.Init(0,SCREEN_HEIGHT/10,SCREEN_WIDTH,SCREEN_HEIGHT*0.65, "");
	juego.SetRel(0,0.1,1,0.65);

	//menus
	menus.Init(0,3*SCREEN_HEIGHT/4,SCREEN_WIDTH,SCREEN_HEIGHT/4, "img/menu.png");
	menus.SetRel(0,0.75,1,0.25);

	//barra
	barra.Init(0,0,SCREEN_WIDTH, SCREEN_HEIGHT/10, "img/barra.png");
	barra.SetRel(0,0,1,0.1);
	
	//pantalla inicial
	total.Init(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, "img/space2.png");
	total.SetRel(0,0,1,1);

	//Actualizar tamaño de cámara
	cam.update(juego);
}

void Game::ActViewPorts()
{
	//Actualizar viewports
	juego.ActParam();
	barra.ActParam();
	menus.ActParam();
	total.ActParam();

	//Actualizar tamaño de cámara
	cam.update(juego);
}

void Game::RenderViewPorts()
{
	//viewports
	
	
	barra.render();
		//elementos que se imprimen en la barra (debe ir detras de la barra)
	menubarra.render();		
	menus.render();
	juego.render();
	renderJuego();
	total.Set();
	mouse.render();

}

void Game::RenderTotal()
{
	total.render();
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
	ast.SetCen(50,50);
	
	ast.setSize(70);
	ast.setMarker(&(tex[4]));


	//cout << typeid(ast).name()<<'\n';

	//inicializacion nave
	for(int i=0;i<60;i++)
	{
	ship[i].SetTex(tex);
	ship[i].setSize(60);
	ship[i].setMarker(&(tex[3]));
	ship[i].SetCen(15*i, 200);
	ship[i].stop();
	}

	std::stringstream recursos[2];
	jugador.getRecursos(recursos);
	menubarra.setRecursos(recursos);
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
			ship[i].render(gRenderer, cam);
		}
	}
	ast.render();

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
	juego.Set();
	
}



void Game::setNombre(std::string nombre)
{
	//nombrejugador=nombre;
	jugador.setName(nombre);
	menubarra.SetName(jugador.getName());
}

void Game::eventjuego(SDL_Event* e)
{
	//eventos de los elementos del juego
	ast.event(e, mouse.getSel(), juego.relatxy());
//	ast.render();
	for(int i=0;i<60;i++)
	{
	ship[i].event(e, mouse.getMrect(), mouse.getMpos());
//	ship[i].render(gRenderer);
	}
	/*if(ast.getSel()) renderMenu();
	juego.Set();*/
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
	//viewport de menu
	menus.Set();

	//renderizamos el menu
	menu.render();

}

void Game::eventMenu(SDL_Event* e)
{
	//eventos del menu
	menu.event(e, menus.relatxy());
	//printf("dentro del menu");
}

void Game::initCaract()
{
	caract.setDim(Vector2(30,10), Vector2(40,40));
}

void Game::renderCaract()
{
	//viewport de menu
	menus.Set();

	//renderizamos el menu
	caract.render();

}

void Game::eventCaract(SDL_Event* e)
{
	//eventos del menu
	caract.event(e, menus.relatxy());
	//printf("dentro del menu");
}

void Game::initBarra()
{
	menubarra.SetName(jugador.getName());

	std::stringstream recursos[2];
	jugador.getRecursos(recursos);
	menubarra.setRecursos(recursos);
}

void Game::renderBarra()
{
	//viewport de menu
	barra.Set();

	//renderizamos el menu
	menubarra.render();

}

void Game::eventBarra(SDL_Event* e)
{
	//eventos de la barra
	menubarra.event(e, barra.relatxy());

}

/*characts* Game::chooseElement(int type)
{
	characts datos;
	switch (type)
	{
	case 1:
		datos.*/