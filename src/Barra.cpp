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
	renderFase();
	//renderOpciones();
}

void Barra::renderName()
{
	Vector2 tamaño;
	nombrejugador.render(gRenderer, &nombrejugador.getDim(),( gWindow.getWidth() - nombrejugador.getDim().x ) / 2, 15);
}

void Barra::SetName(std::string nombre)
{
	SDL_Color color={0,0,255};
	nombrejugador.loadText(nombre, 28, color);
}

void Barra::renderFase()
{
	Vector2 tamaño=fasenum.getDim();

	fasenum.render(gRenderer, &fasenum.getDim(), gWindow.getWidth()*0.8, 15);
}

void Barra::SetFase(int fase)
{
	SDL_Color color={0,0,255};
	//fasenum.loadText(fase.str(), 10, color);

	std:stringstream fas;
	fas.str( " " );
	fas<<fase;
	fasenum.loadText(fas.str(), 40, color, 2);
	//barra.SetFase(fase);
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

	energia.render(gRenderer, &tamañoiconos, 120, 20);
	energianum.render(gRenderer, &energianum.getDim(), 150, 20);

	oro.render(gRenderer, &tamañoiconos, 10, 20);
	oronum.render(gRenderer, &oronum.getDim(), 50, 20);

}

void Barra::setRecursos(std::stringstream recursos[])
{
	SDL_Color color={255,255,0};

	oronum.loadText(recursos[0].str(), 28, color,2);
	energianum.loadText(recursos[1].str().c_str(), 28, color, 2);
}

int Barra::event(SDL_Event* e, SDL_Point xyrel)
{
	return 1;

}
