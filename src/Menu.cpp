#include "Menu.h"


Menu::Menu(void)
{
}


Menu::~Menu(void)
{
}

void Menu::SetBotones()
{
	/*for(int i=0; i<NUMERO_BOTONES; i++)
	{
		botones[i].tex.load=*/
	botones[1].tex.load("edificio.png", gRenderer);
}

void Menu::render()
{
	botones[1].tex.rendermenu(gRenderer, &botonQuad, 20, 20);
}
void Menu::SetBotonQuad(int x, int y, int w, int h)
{
	botonQuad.x=x;
	botonQuad.y=y;
	botonQuad.h=h;
	botonQuad.w=w;
}
