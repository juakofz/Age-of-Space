#include "Ship.h"
#include <cmath>
#include <iostream>
#include "Interacciones.h"

using namespace std;

Ship::Ship():ObjetoMovil(1)
{
	//Vector2 por defecto 0,0;
	//Dirección predeterminada
	dir.x = 1;
	dir.y = 0;
	angle = 0;
	//Destino nulo
	dest.x = 0;
	dest.y = 0;
	//Velocidad máxima
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

	tex = NULL;
}

Ship::Ship(Texture *texture,int siz, Texture *marktex, Vector2 cen2, int p, bool sel):ObjetoMovil(player, sel)
{
	dir.x = 1;
	dir.y = 0;
	angle = 0;
	//Destino nulo
	dest.x = cen.x;
	dest.y = cen.y;
	//Velocidad máxima
	max_vel = 2;
	//Nave parada
	vel.x = 0;
	vel.y = 0;
	//Alcance
	range = 100;

	sel = false;
	sel_angle = 0;

	SetTex(texture);
	setSize(siz);
	setMarker(marktex);
	SetCen(cen2.x, cen2.y);
	player = p;


	stop();
}

Ship::~Ship()
{
}

int Ship::event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m)
{
	int accion = 0;

	//Selección múltiple
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

	//Botón derecho
	if ((e->type == SDL_MOUSEBUTTONDOWN) && (e->button.button == SDL_BUTTON_RIGHT) && (sel))
	{
		//SDL_GetMouseState(&mx, &my);
		dest.x = m.x;
		dest.y = m.y;

		//Dirección
		dir.x = dest.x - cen.x;
		dir.y = dest.y - cen.y;

		angle = (180 * atan2(dir.y, dir.x) / M_PI);

		accion = 1;
	}
	return accion;
}

bool Ship::disparada(Proyectil p)
{
	return Interacciones::impacto(*this, p);

}

Vector2 Ship::getPointyEnd()
{
	Vector2 aux;
	aux.x= cen.x + (tex->getDim().x / 2) * cos(angle*M_PI/180);
	aux.y= cen.y - (tex->getDim().y / 2) * sin(angle*M_PI/180);
	return aux;
}



int Ship::attack(Ship &n)
{
	moveTo(n.GetCen().x, n.GetCen().y);
	//*dest_movil=n->GetCen();
	return 2;
}