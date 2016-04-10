#include "Menu.h"


Menu::Menu(void)
{
}


Menu::~Menu(void)
{
}

void Menu::setBotones(Texture tex[])
{
	for(int i=0;i<NUMERO_BOTONES;i++)
	{
			botones[i].setTexture(&tex[i]);
			botones[i].setPos(40*i +5,5);
	}

}

void Menu::render()
{
	for(int i=0; i<NUMERO_BOTONES;i++) botones[i].render(botondim);

}
void Menu::setBotonQuad(int w, int h)
{
	botondim.x=w;
	botondim.y=h;

}

void Menu::event(SDL_Event* e, SDL_Point xyrel)
{
	for(int i=0; i<2 ;i++) botones[i].event(e, xyrel);				
}

/*void Menu::setTexturas(Texture tex[])
{
	for(int i=0;i<NUMERO_BOTONES;i++) botones[i].setTexture(&tex[i]);
}*/