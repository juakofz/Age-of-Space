#include "EnteSupremo.h"
#include <typeinfo>

EnteSupremo::EnteSupremo(void)
{

}


EnteSupremo::~EnteSupremo(void)
{
}

void EnteSupremo::event(SDL_Event* e)
{
	int mx, my;
	SDL_GetMouseState(&mx, &my);

	//Decide en que viewport estamos segun la posicion del raton
	if(my<barra.getHeight()) //zona de barra
	{
		barra.Set();
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

}

void EnteSupremo::cargarTexturas()
{
	tex[0].load("Nave1.png", gRenderer);
	tex[1].load("asteroide.png", gRenderer);
	tex[2].load("edificio.png", gRenderer);
	tex[3].load("markerW.png", gRenderer);
	tex[4].load("markerW.png", gRenderer);

	tex[3].setColor(255, 100, 0);
	tex[4].setColor(0, 255, 0);


	texOpciones[0].load("edificio.png", gRenderer);
	texOpciones[1].load("markerW.png", gRenderer);
	texOpciones[2].load("Nave1.png", gRenderer);
}

void EnteSupremo::InitViewPorts()
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

void EnteSupremo::ActViewPorts()
{
	juego.ActParam();
	barra.ActParam();
	menus.ActParam();
	total.ActParam();
}

void EnteSupremo::RenderViewPorts()
{
	//viewports
	juego.render();
	barra.render();
		//elementos que se imprimen en la barra (debe ir detras de la barra)
		menubarra.render();
	menus.render();
}

void EnteSupremo::RenderTotal()
{
	total.render();
}

void EnteSupremo::initjuego()
{
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
	ship[i].SetCen(10*i, 0);
	ship[i].stop();
	}
}

void EnteSupremo::renderJuego()
{
	//viewport de juego
	juego.Set();

	//renderizamos los elementos del juego y la seleccion multiple
	mouse.render(gRenderer);
	for(int i=0;i<60;i++) ship[i].render(gRenderer);
	ast.render();

	//movemos la nave y acualizamos
	for(int i=0;i<60;i++)
	{
	ship[i].move();
	ship[i].render(gRenderer);
	}
	if(ast.getSel()) renderMenu();
}



void EnteSupremo::setNombre(std::string nombre)
{
	nombrejugador=nombre;
	menubarra.SetName(nombrejugador);
}

void EnteSupremo::eventjuego(SDL_Event* e)
{
	//eventos de los elementos del juego
	ast.event(e, mouse_selection, juego.relatxy());
	ast.render();
	for(int i=0;i<60;i++)
	{
	ship[i].event(e, mouse_selection, juego.relatxy());
	ship[i].render(gRenderer);
	}
	if(ast.getSel()) renderMenu();
}

void EnteSupremo::initMenu()
{
	menu.setBotones(texOpciones);
	menu.setBotonQuad(40, 40);
}

void EnteSupremo::renderMenu()
{
	//viewport de menu
	menus.Set();

	//renderizamos el menu
	menu.render();

}

void EnteSupremo::eventMenu(SDL_Event* e)
{
	//eventos del menu
	menu.event(e, menus.relatxy());
	printf("dentro del menu");
}