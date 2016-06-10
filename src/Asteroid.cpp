#include "Asteroid.h"

#include <cmath>
#include <iostream>

using namespace std;

//Texture* Asteroid::tex=NULL;
//Texture* Asteroid::marker=NULL;

Asteroid::Asteroid(): GameObject(true)
{
	
}


Asteroid::~Asteroid()
{
}

/*void Asteroid::setMarker(Texture *m)
{
	marker = m;
}*/
int Asteroid::event(SDL_Event* e,SDL_Rect selection, SDL_Point xyrel)
{
	int mx, my;

	mx=xyrel.x;
	my=xyrel.y;

	//Selección múltiple
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


	//Botón derecho
	if ((e->type == SDL_MOUSEBUTTONDOWN) && (e->button.button == SDL_BUTTON_RIGHT) && (sel))
	{
		printf("objetivo");
	}

	return 0;
}

/*void Asteroid::select()
{
	sel = true;
	sel_angle = 0;
}

void Asteroid::deselect()
{
	sel = false;
}*/

//Renderizado
/*void Asteroid::render(Camera cam)
{
	SDL_Point center;
	center.x = cen.x - cam.getPos().x;
	center.y = cen.y - cam.getPos().y;

	
	tex->render(gRenderer, &center, width, height, NULL, angle + 90);

	if(seleccionable)
	{
		SDL_Rect selection;
		selection.x = pos.x - size*0.1;
		selection.y = pos.y - size*0.1;
		selection.w = selection.h = size * 1.2;

		if (sel)
		{
			marker->render(gRenderer, &center, selection.w, selection.h, NULL, sel_angle);
			if (sel_angle > 360) sel_angle = 0;
			else sel_angle++;
		}
	}
}


//Posición

Vector2 Asteroid::GetPos()
{
	return pos;
}

void Asteroid::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
	cen.x = pos.x + tex->getDim().x / 2;
	cen.y = pos.y + tex->getDim().y / 2;
}


//Centro
Vector2 Asteroid::GetCen()
{
	return cen;
}

//Cambia el centro y la posición
void Asteroid::SetCen(float x, float y)
{
	cen.x = x;
	cen.y = y;
	pos.x = cen.x - tex->getDim().x / 2;
	pos.y = cen.y - tex->getDim().y / 2;
}

//Asignación de textura
void Asteroid::SetTex(Texture *t)
{
	tex = t;

}


bool Asteroid::getSel()
{
	return sel;
}

//Tamaño
void Asteroid::setSize(int s)
{
	size = s;
	float scale = s / tex->getDiag();
	//width = tex->getDim().x * scale;
	//height = tex->getDim().y * scale;
}

int Asteroid::getType()
{

	return 1;
}*/