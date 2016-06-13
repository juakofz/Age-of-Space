#include "Edificio.h"


Edificio::Edificio(void): GameObject(true)
{
	vida = 10;
}


Edificio::~Edificio(void)
{
}


int Edificio::event(SDL_Event* e,SDL_Rect selection, SDL_Point xyrel)
{
	int mx, my;

	mx = xyrel.x;
	my = xyrel.y;

	//Selecci�n m�ltiple
	if ((e->type == SDL_MOUSEBUTTONUP) && (e->button.button == SDL_BUTTON_LEFT))
	{
		if (((cen.x > selection.x - tex->getDim().x/2) && (cen.x < (selection.x + selection.w + tex->getDim().x / 2))))
		{
			if (((cen.y > selection.y - tex->getDim().y / 2) && (cen.y < (selection.y + selection.h + tex->getDim().y / 2))))
			{
				select();
			}
			else deselect();
		}
		else deselect();
	}


	//Bot�n derecho
	if ((e->type == SDL_MOUSEBUTTONDOWN) && (e->button.button == SDL_BUTTON_RIGHT) && (sel))
	{
		printf("objetivo");
	}

	return 0;
}

bool Edificio::golpeada()
{
	--vida;
	cout << vida << endl;

	if(vida <= 0) return 1;
	else return 0;
}