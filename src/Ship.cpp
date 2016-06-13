#include "Ship.h"
#include <cmath>
#include <iostream>
#include "Interacciones.h"

using namespace std;

Ship::Ship():ObjetoMovil()
{
	//Vector2 por defecto 0,0;
	//Direcci�n predeterminada
	dir.x = 1;
	dir.y = 0;
	angle = 0;
	//Destino nulo
	dest.x = 0;
	dest.y = 0;
	//Velocidad m�xima
	max_vel = 2;
	//Nave parada
	vel.x = 0;
	vel.y = 0;

	sel = false;
	sel_angle = 0;

	//Color del marcador
	marker_color.r = 0xFF;
	marker_color.g = 0x00;
	marker_color.b = 0x00;
	marker_color.a = 0x00;

	tex=NULL;
}

Ship::Ship(Texture *texture,int siz, Texture *marktex, Vector2 cen2, bool amig):ObjetoMovil(amig)
{
	dir.x = 1;
	dir.y = 0;
	angle = 0;
	//Destino nulo
	dest.x = cen.x;
	dest.y = cen.y;
	//Velocidad m�xima
	max_vel = 2;
	//Nave parada
	vel.x = 0;
	vel.y = 0;

	sel = false;
	sel_angle = 0;

	SetTex(texture);
	setSize(siz);
	setMarker(marktex);
	SetCen(cen2.x, cen2.y);
	amiga=amig;

	stop();


}
Ship::~Ship()
{
}

int Ship::event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m)
{
	/*
	int mx, my;

	mx=m.x;
	my=m.y;
	*/
/*
	//Bot�n izquierdo
	if ((e->type == SDL_MOUSEBUTTONDOWN) && (e->button.button == SDL_BUTTON_LEFT))
	{
		//Selecci�n y deselecci�n individual
		Vector2 size = tex->getDim();
		SDL_GetMouseState(&mx, &my);

		//Clic en la nave
		if (((mx >= pos.x) && (mx <= (pos.x + size.x))) && ((my >= pos.y) && (my <= (pos.y + size.y))))
		{
			//Debug
			//printf("Nave: %.0f, %.0f\n", pos.x, pos.y);
			select();
		}
		else
		{
			deselect();
			//Debug
			//printf("Nada\n");
		}
	}
	*/

	//Selecci�n m�ltiple
	if (e->button.button == SDL_BUTTON_LEFT)
	{
		if (((cen.x > m_sel.x - tex->getDim().x/2) && (cen.x < (m_sel.x + m_sel.w + tex->getDim().x / 2))))
		{
			if (((cen.y > m_sel.y - tex->getDim().y / 2) && (cen.y < (m_sel.y + m_sel.h + tex->getDim().y / 2))))
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
		//SDL_GetMouseState(&mx, &my);
		dest.x = m.x;
		dest.y = m.y;

		//Direcci�n
		dir.x = dest.x - cen.x;
		dir.y = dest.y - cen.y;

		//Normalizaci�n de direcci�n
		/*int unit = 1;
		if (dir.x >= dir.y)
		{
			(dir.x >= 0) ? (unit = 1) : (unit = -1);
			dir.y /= (dir.x * unit);
			dir.x = unit;
		}
		else
		{
			(dir.y >= 0) ? (unit = 1) : (unit = -1);
			dir.x /= (dir.y * unit);
			dir.y = unit;
		}*/
		//Debug
		//printf("Direccion: %.0f, %.0f\n", dir.x, dir.y);
		angle = (180 * atan2(dir.y, dir.x) / M_PI);
		return shoot();
	}
	if ((e->type == SDL_MOUSEBUTTONDOWN) && (e->button.button == SDL_BUTTON_LEFT) && (sel))
	{
		return shoot();
	}

}

int Ship::shoot()
{
	return 1;
}


bool Ship::disparada(Proyectil p)
{
	return Interacciones::impacto(*this, p);

}

Vector2 Ship::getPointyEnd()
{
	Vector2 aux;
	aux.x= cen.x + tex->getDim().x / 2;
	aux.y= cen.y + tex->getDim().y / 2;
	return aux;
}
/*void Ship::select()
{
	sel = true;
	sel_angle = 0;
}

void Ship::deselect()
{
	sel = false;
}

void Ship::move()
{
	if ((abs(cen.x - dest.x) > max_vel) || (abs(cen.y - dest.y) > max_vel)) {

		//Ajuste de velocidades
		vel.x = max_vel * cos(M_PI * angle / 180);
		vel.y = max_vel * sin(M_PI * angle / 180);
		
		//Movimiento
		SetCen(cen.x + vel.x, cen.y + vel.y);
	}
	else
	{
		vel.x = 0;
		vel.y = 0;
	}
}

void Ship::stop()
{
	dest.x = cen.x;
	dest.y = cen.y;
	vel.x = 0;
	vel.y = 0;
}

bool Ship::moveTo(int x, int y)
{
	//vel.x = dir.x;
	//vel.y = dir.y;
	return false;
}
*/
//Renderizado (con rotaci�n y selecci�n)
/*void Ship::render(SDL_Renderer* renderer, Camera cam)
{
	SDL_Point center;
	center.x = cen.x - cam.getPos().x;
	center.y = cen.y - cam.getPos().y;

	tex->render(renderer, &center, width, height, NULL, angle + 90);

	SDL_Rect selection;
	selection.x = pos.x - size*0.1;
	selection.y = pos.y - size*0.1;
	selection.w = selection.h = size * 1.2;

	if (sel)
	{
		marker->render(renderer, &center, selection.w, selection.h, NULL, sel_angle);
		if (sel_angle > 360) sel_angle = 0;
		else sel_angle++;
	}
}

void Ship::setMarker(Texture *m)
{
	marker = m;
}


//Posici�n
Vector2 Ship::GetPos()
{
	return pos;
}

void Ship::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
	cen.x = pos.x + tex->getDim().x / 2;
	cen.y = pos.y + tex->getDim().y / 2;
}

//Velocidad
Vector2 Ship::GetVel()
{
	return vel;
}

void Ship::SetVel(float x, float y)
{
	vel.x = x;
	vel.y = y;
}


//Direcci�n
Vector2 Ship::GetDir()
{
	return dir;
}

void Ship::SetDir(float x, float y)
{
	dir.x = x;
	dir.y = y;
}

//Centro
Vector2 Ship::GetCen()
{
	return cen;
}

//Cambia el centro y la posici�n
void Ship::SetCen(float x, float y)
{
	cen.x = x;
	cen.y = y;
	pos.x = cen.x - tex->getDim().x / 2;
	pos.y = cen.y - tex->getDim().y / 2;
}

//Asignaci�n de textura
void Ship::SetTex(Texture *t)
{
	tex = t;
}

//Tama�o
void Ship::setSize(int s)
{
	size = s;
	float scale = s / tex->getDiag();
	width = tex->getDim().x * scale;
	height = tex->getDim().y * scale;
}*/