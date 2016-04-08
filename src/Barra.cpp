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

	//iconos del oro y la energia
	Texture energia, oro;
	
	//energia.load("Energy.png", gRenderer);
	oro.load("gold.png", gRenderer);

	//tamaño de los iconos
	Vector2 tamaño;
	tamaño.x=30;
	tamaño.y=30;

	//energia.render(gRenderer, &tamaño);
	oro.render(gRenderer, &tamaño, gWindow.getWidth()*0.1);

}

