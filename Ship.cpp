#include "Ship.h"
#include <cmath>
#include <iostream>

using namespace std;

Ship::Ship()
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
}


Ship::~Ship()
{
}

void Ship::event(SDL_Event* e)
{
	int mx, my;

	//Botón izquierdo
	if ((e->type == SDL_MOUSEBUTTONDOWN) && (e->button.button == SDL_BUTTON_LEFT))
	{
		//Selección y deselección
		Vector2 size = tex.getDim();
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
	//Botón derecho
	if ((e->type == SDL_MOUSEBUTTONDOWN) && (e->button.button == SDL_BUTTON_RIGHT) && (sel))
	{
		SDL_GetMouseState(&mx, &my);
		dest.x = mx;
		dest.y = my;
		//Debug
		//printf("Raton: %d, %d\n", mx, my);
	
		//Dirección
		dir.x = dest.x - cen.x;
		dir.y = dest.y - cen.y;
		//Normalización de dirección
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
		//Debug
		//printf("ANGULO: %f, \n", angle);
		//Ship::moveTo(mx, my);

	}

}

void Ship::select()
{
	sel = true;
}

void Ship::deselect()
{
	sel = false;
}

void Ship::move()
{
	if ((abs(cen.x - dest.x) > max_vel) || (abs(cen.y - dest.y) > max_vel)) {
		//cout << "Me tengo que mover!" << endl;
		//cout << "Estoy en " << cen.x << ", " << cen.y << endl;
		//cout << "Tengo que ir a " << dest.x << ", " << dest.y << endl;
		//cout << "Apunto a" << angle << " grados" << endl;
		//Ajuste de velocidades
		vel.x = max_vel * cos(M_PI * angle / 180);
		vel.y = max_vel * sin(M_PI * angle / 180);
		//cout << "Voy con velocidad " << vel.x << ", " << vel.y << endl;
		//Movimiento
		SetCen(cen.x + vel.x, cen.y + vel.y);
		//cout << "Me he movido a  " << cen.x << ", " << cen.y << endl;
		//system("PAUSE");
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

//Renderizado (con rotación y selección)
void Ship::render(SDL_Renderer* renderer)
{
	/*float angle = 90 + (180 * atan2(dir.y, dir.x) /M_PI);*/
	tex.render(renderer, pos.x, pos.y, NULL, angle+90);
	//Marcador de selección
	if (sel == true)
	{
		SDL_Rect rec_sel;
		rec_sel.x = pos.x;
		rec_sel.y = pos.y;
		rec_sel.h = tex.getDim().x;
		rec_sel.w = tex.getDim().y;
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);;
		SDL_RenderDrawRect(renderer, &rec_sel);
	}
}

//Posición
Vector2 Ship::GetPos()
{
	return pos;
}

void Ship::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
	cen.x = pos.x + tex.getDim().x / 2;
	cen.y = pos.y + tex.getDim().y / 2;
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


//Dirección
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

//Cambia el centro y la posición
void Ship::SetCen(float x, float y)
{
	cen.x = x;
	cen.y = y;
	pos.x = cen.x - tex.getDim().x / 2;
	pos.y = cen.y - tex.getDim().y / 2;
}