#include "ObjetoMovil.h"


ObjetoMovil::ObjetoMovil(bool selec):GameObject(selec)
{
	
	//Vector2 por defecto 0,0;
	//Dirección predeterminada
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

	sel = false;
	sel_angle = 0;

	tex=NULL;
}


ObjetoMovil::~ObjetoMovil()
{
}

int ObjetoMovil::event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m)
{
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
	}
	return 0;

}

void ObjetoMovil::render(Camera cam)
{
	move();
	GameObject::render(cam);
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
	dest.x=x;
	dest.y=y;

	dir.x = dest.x - cen.x;
	dir.y = dest.y - cen.y;

	angle = (180 * atan2(dir.y, dir.x) / M_PI);
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

//Dirección
Vector2 ObjetoMovil::GetDir()
{
	return dir;
}

void ObjetoMovil::SetDir(float x, float y)
{
	dir.x = x;
	dir.y = y;
}
