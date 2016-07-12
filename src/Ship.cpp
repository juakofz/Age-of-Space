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
	turn_rad = 25;

	//Nave parada
	vel.x = 0;
	vel.y = 0;
	state = 0;

	//Alcance
	range = 150;
	sight = 250;

	firerate = 3;

	sel = false;
	sel_angle = 0;

	//Color del marcador
	marker_color.r = 0xFF;
	marker_color.g = 0x00;
	marker_color.b = 0x00;
	marker_color.a = 0x00;

	order.start();
	target = 0;
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
	turn_rad = 20;

	//Nave parada
	vel.x = 0;
	vel.y = 0;
	state = 0;

	//Alcance
	range = 150;
	sight = 250;

	firerate = 3;

	sel = false;
	sel_angle = 0;

	SetTex(texture);
	setSize(siz);
	setMarker(marktex);
	SetCen(cen2.x, cen2.y);
	player = p;

	order.start();

	target = 0;
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
		setDest(m.x, m.y);
		setState(1);
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

float Ship::getRange()
{
	return range;
}

bool Ship::inRange(Vector2 p)
{
	return(cen.distancia(p) <= range);
}

bool Ship::inRange(Ship * s)
{
	return inRange(s->GetCen());
}


float Ship::getSight()
{
	return sight;
}

bool Ship::inSight(Vector2 p)
{
	return(cen.distancia(p) <= sight);
}

bool Ship::inSight(Ship * s)
{
	return inSight(s->GetCen());
}


bool Ship::attack()
{
	//cout<<"pium?"<<endl;
	//cout<<t_shoot.getSecs()<<1.0F/firerate<<endl;
	if (t_shoot.isStarted() && (t_shoot.getSecs() > (1.0F / firerate)))
	{
		t_shoot.restart();
		//cout<<"piem!!!"<<endl;
		return true; //pium
	}
	if (!t_shoot.isStarted())
	{
		t_shoot.start();
		return false; //no pium
	}

	return false;
}

Vector2 Ship::shoot()
{
	Vector2 aux;
	aux.x = cen.x + dir.x * range;
	aux.y = cen.y + dir.y * range;
	return aux;
}

int Ship::getState()
{
	return state;
}

void Ship::setState(int s)
{
	state = s;
}

Timer * Ship::getTimer()
{
	return &order;
}

bool Ship::turn()
{
	if (target) return ( ObjetoMovil::turn(target->GetCen().x, target->GetCen().y));
	else return (ObjetoMovil::turn(dest.x, dest.y));
}

void Ship::turn(Vector2 t)
{
	ObjetoMovil::turn(t.x, t.y);
}

void Ship::setTarget(Ship * t)
{
	target = t;
	dest = target->GetCen();
	
}

void Ship::updateTarget()
{
	if (!target) return;
	else dest = target->GetCen();
}

bool Ship::checkTarget()
{
	return target;
}

Ship * Ship::getTarget()
{
	return target;
}

bool Ship::onTarget(Vector2 t, float err)
{
	//Vector2 aux = cen - t;
	Vector2 aux = t- cen;
	//cout<<(int)abs(dir.argumento() - aux.argumento())%360<<"   ";
	//cout<<(((int)abs(dir.argumento() - aux.argumento())%360 <= err) ||((int)abs(dir.argumento() - aux.argumento())%360 >= 360-err))<<endl;
	return (((int)abs(dir.argumento() - aux.argumento())%360 <= err) ||((int)abs(dir.argumento() - aux.argumento())%360 >= 360-err));
}

bool Ship::onTarget(float err)
{
	if (!target) return false; //No target
	//Vector2 aux = cen - target->GetCen();
	Vector2 aux = target->GetCen()- cen;
	//cout<<(int)abs(dir.argumento() - aux.argumento())%360<<"   ";
	//cout<<(((int)abs(dir.argumento() - aux.argumento())%360 <= err) ||((int)abs(dir.argumento() - aux.argumento())%360 >= 360-err))<<endl;
	return (((int)abs(dir.argumento() - aux.argumento())%360 <= err) || ((int)abs(dir.argumento() - aux.argumento())%360 >= 360-err));
}

float Ship::targetDist()
{
	if (!target) return cen.distancia(dest);
	return cen.distancia(target->GetCen());
}