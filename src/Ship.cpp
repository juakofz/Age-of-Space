#include "Ship.h"
#include <cmath>


Ship::Ship()
{

	//Dirección predeterminada
	dir.x = 1;
	dir.y = 0;

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
			printf("Nave: %.0f, %.0f\n", pos.x, pos.y);
			select();
		}
		else
		{
			deselect();
			printf("Nada\n");
		}
	}
	//Botón derecho
	if ((e->type == SDL_MOUSEBUTTONDOWN) && (e->button.button == SDL_BUTTON_RIGHT))
	{
		SDL_GetMouseState(&mx, &my);
		printf("Raton: %d, %d\n", mx, my);
		if (sel) {
			dir.x = mx - pos.x;
			dir.y = my - pos.y;
			printf("Direccion: %.0f, %.0f\n", dir.x, dir.y);
			float angle = 90 + (180 * atan2(dir.y, dir.x) / M_PI);
			printf("ANGULO: %f, \n", angle);
		}
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

void Ship::move() {
	pos.x += vel.x;
	pos.y += vel.y;
}

bool Ship::moveTo(int x, int y)
{
	//dir.x = (x - pos.x);
	//dir.y = (y - pos.y);
	return false;
}

//Renderizado (con rotación y selección)
void Ship::render(SDL_Renderer* renderer)
{
	float angle = 90 + (180 * atan2(dir.y, dir.x) /M_PI);
	tex.render(renderer, pos.x, pos.y, NULL, angle);
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