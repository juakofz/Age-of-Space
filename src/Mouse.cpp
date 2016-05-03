#include "Mouse.h"

using namespace std;

Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

<<<<<<< HEAD
void Mouse::setCursor(Texture * c)
{
	cursor = c;
}

void Mouse::update(SDL_Event *e, SDL_Point xyrel)
{
	//Posición

	//SDL_GetMouseState(&pos.x, &pos.y);

	pos.x=xyrel.x;
	pos.y=xyrel.y;
=======
void Mouse::update(SDL_Event *e)
{
	//Posición
	SDL_GetMouseState(&pos.x, &pos.y);
>>>>>>> refs/remotes/origin/development

	//Click
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
<<<<<<< HEAD
		//SDL_GetMouseState(&press.x, &press.y);

		press.x=xyrel.x;
		press.y=xyrel.y;
=======
		SDL_GetMouseState(&press.x, &press.y);
>>>>>>> refs/remotes/origin/development
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
<<<<<<< HEAD
	cursor->render(renderer, pos.x, pos.y, NULL);

=======
>>>>>>> refs/remotes/origin/development
	if (active) {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawRect(renderer, &rect);
	}
}


SDL_Rect Mouse::getSel()
{
	return rect;
}