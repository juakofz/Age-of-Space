#include "Barra.h"
#include "Global.h"
#include <sstream>

Barra::Barra(void)
{
}


Barra::~Barra(void)
{
}

void Barra::render()
{
	//actRecursos();
	viewport.render();

	renderName();
	renderRecursos();
	//renderOpciones();
}

void Barra::renderName()
{
	Vector2 tamaño;
	tamaño.x=gWindow.getWidth()*0.5;
	tamaño.y=25;
	nombrejugador.render(gRenderer, &tamaño, gWindow.getWidth()*0.25, 20);
}

void Barra::SetName(std::string nombre)
{
	SDL_Color color={0,0,255};
	nombrejugador.loadText(nombre, 10, color);
}

void Barra::renderRecursos()
{
	SDL_Color color={255,255,0};

	//iconos del oro y la energia
	Texture energia, oro;
	Texture energiaVal, oroVal;
	energia.load("img/energy3.png", gRenderer);
	oro.load("img/gold.png", gRenderer);

	//tamaño de los iconos
	Vector2 tamañoiconos;
	Vector2 tamañotexto;
	tamañoiconos.x=30;
	tamañoiconos.y=30;
	tamañotexto.x=60;
	tamañotexto.y=30;

	energia.render(gRenderer, &tamañoiconos, 120);
	energianum.render(gRenderer, &tamañotexto, 150);

	oro.render(gRenderer, &tamañoiconos, 10);
	oronum.render(gRenderer, &tamañotexto, 50);

}

void Barra::setRecursos(std::stringstream recursos[])
{
	SDL_Color color={255,255,0};

	oronum.loadText(recursos[0].str(), 10, color,2);
	energianum.loadText(recursos[1].str().c_str(), 10, color, 2);
}

int Barra::event(SDL_Event* e, SDL_Point xyrel)
{
	return 1;

}
