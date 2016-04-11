#include "Barra.h"
#include "Global.h"
#include <sstream>

Barra::Barra(void)
{
}


Barra::~Barra(void)
{
}

void Barra::render(std::stringstream recursos[])
{
	//actRecursos();
	renderRecursos(recursos);

	renderName();

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

void Barra::renderRecursos(std::stringstream recursos[])
{
	SDL_Color color={255,255,0};

	//iconos del oro y la energia
	Texture energia, oro;
	Texture energiaVal, oroVal;
	energia.load("Energy.png", gRenderer);
	oro.load("gold.png", gRenderer);

	//tamaño de los iconos
	Vector2 tamañoiconos;
	Vector2 tamañotexto;
	tamañoiconos.x=30;
	tamañoiconos.y=30;
	tamañotexto.x=60;
	tamañotexto.y=30;

	energia.render(gRenderer, &tamañoiconos, 120);
	oro.render(gRenderer, &tamañoiconos, 10);
	oroVal.render(gRenderer, &tamañotexto, 50);
	cout<<"imprimiendo valores";


	energiaVal.loadText(recursos[0].str(), 10, color);
	energiaVal.render(gRenderer, &tamañotexto, 150);

	oroVal.loadText(recursos[1].str(), 10, color);
	oroVal.render(gRenderer, &tamañotexto, 50);
}

void Barra::setRecursos(std::stringstream recursos[])
{
	SDL_Color color={255,255,0};

	oroVal.loadText(recursos[0].str(), 10, color);
	cout<<recursos[0].str().c_str()<<'\n';
	//energiaVal.loadText(recursos[1].str().c_str(), 10, color);
	energiaVal.loadText("energia", 10, color);
}