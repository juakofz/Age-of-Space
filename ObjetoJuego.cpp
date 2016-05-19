#include "ObjetoJuego.h"


Texture* ObjetoJuego::tex=NULL;
Texture* ObjetoJuego::marker=NULL;

ObjetoJuego::ObjetoJuego()
{
	sel = false;

	//color del marcador
	/*marker_color.r = 0x00;
	marker_color.g = 0xFF;
	marker_color.b = 0x00;
	marker_color.a = 0x00;*/
	sel_angle=0;
}


ObjetoJuego::~ObjetoJuego()
{
}

void ObjetoJuego::setMarker(Texture *m)
{
	marker = m;
}
void ObjetoJuego::event(SDL_Event* e,SDL_Rect selection, SDL_Point xyrel)
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
}

void ObjetoJuego::select()
{
	sel = true;
	sel_angle = 0;
}

void ObjetoJuego::deselect()
{
	sel = false;
}

//Renderizado
void ObjetoJuego::render()
{
	//renderizado de la textura
	tex->render(gRenderer,(int)pos.x,(int)pos.y);


	SDL_Rect selection;
	selection.x = pos.x - size*0.1;
	selection.y = pos.y - size*0.1;
	selection.w = selection.h = size * 1.2;
	SDL_Point centro = cen.convert_int();

	//Marcador de selección
	if (sel == true)
	{
		marker->render(gRenderer, &centro, selection.w, selection.h, NULL, sel_angle);
		if (sel_angle > 360) sel_angle = 0;
		else sel_angle++;
	}
}

//Posición
Vector2 ObjetoJuego::GetPos()
{
	return pos;
}

void ObjetoJuego::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
	cen.x = pos.x + tex->getDim().x / 2;
	cen.y = pos.y + tex->getDim().y / 2;
}


//Centro
Vector2 ObjetoJuego::GetCen()
{
	return cen;
}

//Cambia el centro y la posición
void ObjetoJuego::SetCen(float x, float y)
{
	cen.x = x;
	cen.y = y;
	pos.x = cen.x - tex->getDim().x / 2;
	pos.y = cen.y - tex->getDim().y / 2;
}

//Asignación de textura
void ObjetoJuego::SetTex(Texture *t)
{
	tex = t;
}

bool ObjetoJuego::getSel()
{
	return sel;
}
//Tamaño
void ObjetoJuego::setSize(int s)
{
	size = s;
	float scale = s / tex->getDiag();
	//width = tex->getDim().x * scale;
	//height = tex->getDim().y * scale;
}

int ObjetoJuego::getType()
{

	return 1;
}
