#include "Mouse.h"

using namespace std;

Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

void Mouse::update(SDL_Event *e, SDL_Point xyrel)
{
	//Posición

	//SDL_GetMouseState(&pos.x, &pos.y);

	pos.x=xyrel.x;
	pos.y=xyrel.y;

	//Click
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		//SDL_GetMouseState(&press.x, &press.y);

		press.x=xyrel.x;
		press.y=xyrel.y;
	}
	
	//Rectángulo de selección
	if (e->button.button == SDL_BUTTON_LEFT)
	{
		active = true;
		//Eje x
		if ((press.x > pos.x))
		{
			rect.x = pos.x;
			rect.w = press.x - pos.x;
		}
		else
		{
			rect.x = press.x;
			rect.w = pos.x - press.x;
		}
		//Eje y
		if ((press.y > pos.y))
		{
			rect.y = pos.y;
			rect.h = press.y - pos.y;
		}
		else
		{
			rect.y = press.y;
			rect.h = pos.y - press.y;
		}
	}

	//Soltar
	if (e->type == SDL_MOUSEBUTTONUP)
	{
		active = false;
	}
}

void Mouse::render(SDL_Renderer *renderer)
{
	if (active) {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawRect(renderer, &rect);
	}
}


SDL_Rect Mouse::getSel()
{
	return rect;
}