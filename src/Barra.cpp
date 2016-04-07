#include "Barra.h"
#include "Global.h"

Barra::Barra(void)
{
}


Barra::~Barra(void)
{
}

void Barra::render()
{
	//actRecursos();
	renderRecursos();

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

void Barra::renderRecursos()
{
	SDL_Color color={255,255,0};

	Texture energia, oro;
	energia.loadText("energia", 10, color);
	oro.loadText("oro", 10, color);

	Vector2 tamaño;
	tamaño.x=gWindow.getWidth()*0.1;
	tamaño.y=15;
	energia.render(gRenderer, &tamaño, gWindow.getWidth()*0, 10);
	oro.render(gRenderer, &tamaño, gWindow.getWidth()*0.1, 10);

}

