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
			botones[i].setPos(45*i +5,5);
	}
	for(int i=0;i<NUMERO_BOT_GENERALES;i++)
	{
		botonesgenerales[i].setTexture(tex+i+NUMERO_BOTONES);
		botonesgenerales[i].setPos(45*i+50, 95);
	}

}

void Menu::render()
{
	viewport.render();
}

void Menu::Open()
{
	viewport.Set();
	for(int i=0; i<NUMERO_BOTONES;i++) botones[i].render(botondim);
	for(int i=0; i<NUMERO_BOT_GENERALES;i++) botonesgenerales[i].render(botondim);

}

void Menu::setBotonQuad(int w, int h)
{
	botondim.x=w;
	botondim.y=h;

}

int Menu::event(SDL_Event* e, SDL_Point xyrel)
{
	for(int i=0; i<NUMERO_BOTONES;i++) if(botones[i].event(e, xyrel)) return i;
	for(int i=0; i<NUMERO_BOT_GENERALES;i++) if(botonesgenerales[i].event(e, xyrel)) return (i+NUMERO_BOTONES);
}

/*void Menu::setTexturas(Texture tex[])
{
	for(int i=0;i<NUMERO_BOTONES;i++) botones[i].setTexture(&tex[i]);
}*/