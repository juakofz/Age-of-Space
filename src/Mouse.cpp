#include "Mouse.h"

using namespace std;

Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> refs/remotes/origin/development
void Mouse::setCursor(Texture * c)
{
	cursor = c;
}

<<<<<<< HEAD
void Mouse::update(SDL_Event *e, SDL_Point xyrel)
=======
bool Mouse::update(SDL_Event *e, SDL_Point xyrel)
>>>>>>> refs/remotes/origin/development
{
	//Posici�n

	//SDL_GetMouseState(&pos.x, &pos.y);

	pos.x=xyrel.x;
	pos.y=xyrel.y;
<<<<<<< HEAD
=======
void Mouse::update(SDL_Event *e)
{
	//Posici�n
	SDL_GetMouseState(&pos.x, &pos.y);
>>>>>>> refs/remotes/origin/development
=======
>>>>>>> refs/remotes/origin/development

	//Click
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
<<<<<<< HEAD
<<<<<<< HEAD
		//SDL_GetMouseState(&press.x, &press.y);

		press.x=xyrel.x;
		press.y=xyrel.y;
=======
		SDL_GetMouseState(&press.x, &press.y);
>>>>>>> refs/remotes/origin/development
=======
		//SDL_GetMouseState(&press.x, &press.y);
		press.x=xyrel.x;
		press.y=xyrel.y;
>>>>>>> refs/remotes/origin/development
	}
	
	//Rect�ngulo de selecci�n
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
<<<<<<< HEAD
=======

	return active;
}

void Mouse::scroll(Camera cam)
{
	int margin = 10;
	float speed = 20;

	SDL_GetMouseState(&pos.x, &pos.y);
	//cout << "Mouse: --  " << pos.x << " , " << pos.y << endl;
	
	//Lineal, no inertia
	if (cam.getCen().x >= 0)
	{
		if (pos.x < margin)
		{
			cam.move(-speed, 0);
			cout << "Left" << endl;
		}
		if (pos.x > gWindow.getWidth() - margin)
		{
			cam.move(speed, 0);
			cout << "Right" << endl;
		}
	}
	if (cam.getCen().y >= 0)
	{
		if (pos.y < margin)
		{
			cam.move(0, -speed);
			cout << "Up" << endl;
		}
		if (pos.y > gWindow.getHeight() - margin)
		{
			cam.move(0, speed);
			cout << "Down" << endl;
		}
	}
	//cout << "Scroll: --  " << cam.getCen().x << " , " << cam.getCen().y << endl;
>>>>>>> refs/remotes/origin/development
}

void Mouse::render(SDL_Renderer *renderer)
{
<<<<<<< HEAD
<<<<<<< HEAD
	cursor->render(renderer, pos.x, pos.y, NULL);

=======
>>>>>>> refs/remotes/origin/development
	if (active) {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
=======
	cursor->render(renderer, pos.x, pos.y, NULL);

	if (active) {
		SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0xFF, 0xFF);
>>>>>>> refs/remotes/origin/development
		SDL_RenderDrawRect(renderer, &rect);
	}
}


SDL_Rect Mouse::getSel()
{
	return rect;
}