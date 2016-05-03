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
	//flag de selecci�n m�ltiple con el rat�n
	static bool seleccion=false;

	int mx, my;
	SDL_GetMouseState(&mx, &my);

	//Decide en que viewport estamos segun la posicion del raton
	if(seleccion || (my>barra.getHeight() && my<menus.getY())) //zona de juego
	{
		juego.Set();
		eventjuego(e);
		//printf("en juego");
		juego.event(e);
		seleccion = mouse.update(e, juego.relatxy());
		mouse_selection = mouse.getSel();
		numviewport=3;
	}

	//si estamos haciendo selecci�n en el juego no entra en los otros viewports

	if(seleccion==false)
	{
		if(my<barra.getHeight()) //zona de barra
		{
			barra.Set();
			//printf("en barra");
			mouse.update(e, barra.relatxy());
			numviewport=1;
		}
		if(my>menus.getY()) //zona de menus
		{
			menus.Set();
			//printf("menus");
			menus.event(e);
			eventMenu(e);
			mouse.update(e, menus.relatxy());
			numviewport=2;
		}
	}		
}

void Game::cargarTexturas()
{
	tex[0].load("Nave1.png");
	tex[1].load("asteroide.png");
	tex[2].load("edificio.png");
	tex[3].load("markerW.png");
	tex[4].load("markerW.png");
	tex[5].load("Cursor.png");

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
	juego.Init(0,SCREEN_HEIGHT/10,SCREEN_WIDTH,SCREEN_HEIGHT*0.65, "space.png");
	juego.SetRel(0,0.1,1,0.65);

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
	
	barra.render();
		//elementos que se imprimen en la barra (debe ir detras de la barra)
	/*std::stringstream recursos[2];
	jugador.getRecursos(recursos);
	menubarra.setRecursos(recursos);*/
	if(numviewport==1) 	mouse.render(gRenderer);
		menubarra.render();
	menus.render();
	if(numviewport==2) mouse.render(gRenderer);
	juego.render();
	renderJuego();
	if(numviewport==3) mouse.render(gRenderer);
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
	

	//renderizamos los elementos del juego y la seleccion multiple
	for(int i=0;i<60;i++) ship[i].render(gRenderer);
	ast.render();

	//movemos la nave y acualizamos
	for(int i=0;i<60;i++)
	{
	ship[i].move();
	ship[i].render(gRenderer);
	}
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
	ast.event(e, mouse_selection, juego.relatxy());
//	ast.render();
	for(int i=0;i<60;i++)
	{
	ship[i].event(e, mouse_selection, juego.relatxy());
//	ship[i].render(gRenderer);
	}
	/*if(ast.getSel()) renderMenu();
	juego.Set();*/
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