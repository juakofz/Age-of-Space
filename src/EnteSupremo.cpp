#include "EnteSupremo.h"


EnteSupremo::EnteSupremo(void)
{

}


EnteSupremo::~EnteSupremo(void)
{
}

void EnteSupremo::setViewPort(SDL_Event* e)
{

	int mx, my;
	SDL_GetMouseState(&mx, &my);
	if(my<barra.getHeight())
	{
	barra.Set();
	//printf("en barra");
	}
	if(my>menus.getY())
	{
		menus.Set();
		//printf("menus");
		menus.event(e);
	}
	if(my>barra.getHeight() && my<menus.getY())
	{
		juego.Set();
		//printf("en juego");
		juego.event(e);
	}
	SDL_Rect view;
	SDL_RenderGetViewport(gRenderer, &view);

	//printf("\n estamos en: %d %d %d %d\n", view.x, view.y, view.w, view.h);

}

void EnteSupremo::InitViewPorts()
{
	menus.Init(0,3*SCREEN_HEIGHT/4,SCREEN_WIDTH,SCREEN_HEIGHT/4, "menu.png");
	juego.Init(0,SCREEN_HEIGHT/10,SCREEN_WIDTH,3*SCREEN_HEIGHT/4, "space.png");
	menus.SetRel(0,0.75,1,0.25);
	juego.SetRel(0,0.1,1,0.75);
	barra.Init(0,0,SCREEN_WIDTH, SCREEN_HEIGHT/10, "barra.png");
	barra.SetRel(0,0,1,0.1);
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
	juego.render();

	barra.render();

	menus.render();
	if (ast.getSel()) printf("menu de asteroide");
}

void EnteSupremo::event(SDL_Event* e)
{
	//juego.event(e);
	//menus.event(e);
	ast.event(e, juego.relatxy());
	ast.render();
}

void EnteSupremo::RenderTotal()
{

	total.render();
}

void EnteSupremo::initjuego()
{
	ast.SetCen(50,50);
	ast.tex.load("asteroide.png", gRenderer);
}

void EnteSupremo::renderJuego()
{
	juego.Set();
	ast.render();
}