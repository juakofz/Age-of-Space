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
	int mx, my;
	SDL_GetMouseState(&mx, &my);

	//Decide en que viewport estamos segun la posicion del raton
	if(my<barra.getHeight()) //zona de barra
	{
		barra.Set();
		mouse.update(e, barra.relatxy());
		mouse.render(gRenderer);
		//printf("en barra");
	}
	if(my>menus.getY()) //zona de menus
	{
		menus.Set();
		//printf("menus");
		menus.event(e);
		eventMenu(e);
	}
	if(my>barra.getHeight() && my<menus.getY()) //zona de juego
	{
		juego.Set();
		eventjuego(e);
		//printf("en juego");
		juego.event(e);
	}
	//eventos del raton
	mouse.update(e, juego.relatxy());
	mouse_selection = mouse.getSel();

	//Keyboard events
	keyboard.update(e, camera);

}

void Game::cargarTexturas()
{
	tex[0].load("Nave1.png");
	tex[1].load("asteroide.png");
	tex[2].load("edificio.png");
	tex[3].load("markerW.png");
	tex[4].load("markerW.png");
	tex[5].load("Cursor.png");
	tex[6].load("Background.png");
	tex[7].load("Grid.png");

	tex[3].setColor(255, 100, 0);
	tex[4].setColor(0, 255, 0);


	texOpciones[0].load("edificio.png");
	texOpciones[1].load("markerW.png");
	texOpciones[2].load("Nave1.png");
	texOpciones[3].load("atras.png");
	texOpciones[4].load("cerrar.png");
}

void Game::InitViewPorts()
{

	//juego
	juego.Init(0,SCREEN_HEIGHT/10,SCREEN_WIDTH,SCREEN_HEIGHT*0.65);
	juego.SetRel(0,0.1,1,0.65);

	//Camera
	SDL_Rect temp;
	temp.x = 100;
	temp.y = 100;
	temp.w = SCREEN_WIDTH, SCREEN_HEIGHT*0.65;
	temp.h = SCREEN_HEIGHT / 10;
	camera.setRect(temp);
	camera.setCen(temp.x + temp.w / 2, temp.y + temp.h / 2);
	camera.setZoom(1);

	//menus
	menus.Init(0,3*SCREEN_HEIGHT/4,SCREEN_WIDTH,SCREEN_HEIGHT/4, "menu.png");
	menus.SetRel(0,0.75,1,0.25);

	//barra
	barra.Init(0,0,SCREEN_WIDTH, SCREEN_HEIGHT/10, "barra.png");
	barra.SetRel(0,0,1,0.1);
	
	//pantalla inicial
	total.Init(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, "space2.png");
	total.SetRel(0,0,1,1);
}

void Game::ActViewPorts()
{
	juego.ActParam();
	barra.ActParam();
	menus.ActParam();
	total.ActParam();
}

void Game::RenderViewPorts()
{
	//viewports
	juego.render();
	barra.render();
	
		//elementos que se imprimen en la barra (debe ir detras de la barra)
	/*std::stringstream recursos[2];
	jugador.getRecursos(recursos);
	menubarra.setRecursos(recursos);*/
	menubarra.render();
	menus.render();
	//mouse.render(gRenderer);
	total.Set();
	mouse.render(gRenderer);
}

void Game::RenderTotal()
{
	total.render();
	//mouse.render(gRenderer);
}

void Game::initjuego()
{
	//Inicializaci�n del cursor
	mouse.setCursor(tex + 5);

	//Inicializaci�n del mapa
	map.setBackground(tex + 6);
	map.setMap(tex + 7);

	//inicializacion asteroide
	ast.SetTex(tex+1);
	ast.SetCen(50,50);
	
	ast.setSize(70);
	ast.setMarker(&(tex[4]));

	//printf("%c", typeid(ast).name());

	cout << typeid(ast).name()<<'\n';

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
	
	//Renderizado del mapa
	map.render(camera.getRect());

	//renderizamos los elementos del juego y la seleccion multiple
	for(int i = 0; i < 60; i++) ship[i].render(gRenderer);
	ast.render();

	//movemos la nave y acualizamos
	for(int i = 0; i < 60; i++)
	{
	ship[i].move();
	ship[i].render(gRenderer);
	}
	if(ast.getSel()) 
	{
			renderMenu();
			int type=ast.getType();
	}
	mouse.render(gRenderer);
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
	ast.event(e, mouse_selection, juego.relatxy());
//	ast.render();
	for(int i=0;i<60;i++)
	{
	ship[i].event(e, mouse_selection, juego.relatxy());
//	ship[i].render(gRenderer);
	}
	if(ast.getSel()) renderMenu();
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