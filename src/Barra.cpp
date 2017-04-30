#include "Barra.h"
#include "Global.h"
#include <sstream>

Barra::Barra(void)
{
	color.r = 255;
	color.g = 255;
	color.b = 0;
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
	renderVida();
	//renderOpciones();
}

void Barra::renderName()
{
	Vector2 tamaño;
	nombrejugador.render(g_Renderer, &nombrejugador.getDim(), (g_Window.getWidth() - nombrejugador.getDim().x) / 2, 15);
}

void Barra::SetName(std::string nombre)
{
	//SDL_Color color={0,0,255};
	nombrejugador.loadText(nombre, 28, color);
}

void Barra::renderFase()
{
	Vector2 tamaño = fasenum.getDim();
	
		fasenum.render(g_Renderer, &fasenum.getDim(), g_Window.getWidth()*0.8, 15);
}

void Barra::SetFase(int fase)
{
	//SDL_Color color = { 0,0,255 };

	//fasenum.loadText(fase.str(), 10, color);
	std:stringstream fas;
	fas.str(" ");
	fas << fase;
	fasenum.loadText(fas.str(), 40, color, 2);
	//barra.SetFase(fase);
}

void Barra::renderRecursos()
{
	SDL_Color color={255,255,0};

	//iconos del oro y la energia
	Texture energia, oro;
	Texture energiaVal, oroVal;
	energia.load("img/energy3.png", g_Renderer);
	oro.load("img/gold.png", g_Renderer);

	//tamaño de los iconos
	Vector2 tamañoiconos;
	Vector2 tamañotexto;
	tamañoiconos.x=30;
	tamañoiconos.y=30;

	energia.render(g_Renderer, &tamañoiconos, 120, 20);
	energianum.render(g_Renderer, &energianum.getDim(), 150, 20);

	oro.render(g_Renderer, &tamañoiconos, 10, 20);
	oronum.render(g_Renderer, &oronum.getDim(), 50, 20);

}

void Barra::setRecursos(std::stringstream recursos[])
{
	SDL_Color color={255,255,0};

	oronum.loadText(recursos[0].str(), 40, color, 2);
	energianum.loadText(recursos[1].str().c_str(), 40, color, 2);
}

int Barra::event(SDL_Event* e, SDL_Point xyrel)
{
	return 1;

}

void Barra::setVida(int vid)
{
	std:stringstream v;
	v.str(" ");
	v << vid;
	vida.loadText(v.str(), 40, color, 2);
}

void Barra::renderVida()
{
	Vector2 tamaño = vida.getDim();
	
	vida.render(g_Renderer, &vida.getDim(), g_Window.getWidth()*0.9, 15);
}