#include "Menu.h"


Menu::Menu(void)
{
}


Menu::~Menu(void)
{
}

void Menu::SetBotones()
{


}

void Menu::render()
{
	//for(int i=0; i<2;i++) botones[i].tex.rendermenu(gRenderer, &botondim, 50*i+10, 20);

}
void Menu::SetBotonQuad(int w, int h)
{
	botondim.x=w;
	botondim.y=h;

}

void Menu::event(SDL_Event* e)
{
	for(int i=0; i<2 ;i++) botones[i].event(e);				
}
	