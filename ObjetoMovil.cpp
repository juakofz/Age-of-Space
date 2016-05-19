#include "ObjetoMovil.h"


ObjetoMovil::ObjetoMovil(void):GameObject(true)
{
	
	//Vector2 por defecto 0,0;
	//Direcci�n predeterminada
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

	tex=NULL;
}


ObjetoMovil::~ObjetoMovil()
{
}

void ObjetoMovil::event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m)
{
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

		angle = (180 * atan2(dir.y, dir.x) / M_PI);
	}

}

void ObjetoMovil::move()
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

void ObjetoMovil::stop()
{
	dest.x = cen.x;
	dest.y = cen.y;
	vel.x = 0;
	vel.y = 0;
}

bool ObjetoMovil::moveTo(int x, int y)
{
	//vel.x = dir.x;
	//vel.y = dir.y;
	return false;
}

//Velocidad
Vector2 ObjetoMovil::GetVel()
{
	return vel;
}

void ObjetoMovil::SetVel(float x, float y)
{
	vel.x = x;
	vel.y = y;
}

//Direcci�n
Vector2 ObjetoMovil::GetDir()
{
	return dir;
}

void ObjetoMovil::SetDir(float x, float y)
{
	dir.x = x;
	dir.y = y;
}
