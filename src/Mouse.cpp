#include "Mouse.h"

using namespace std;

Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

void Mouse::setCursor(Texture * c)
{
	cursor = c;
}

<<<<<<< HEAD
=======
bool Mouse::update(SDL_Event *e, SDL_Point xyrel)
{
	//Posición

	//SDL_GetMouseState(&pos.x, &pos.y);
>>>>>>> origin/master

//Event + relative position
bool Mouse::update(SDL_Event *e, SDL_Point xyrel)
{
	//Update relative position
	r_pos.x = xyrel.x;
	r_pos.y = xyrel.y;

	//Click event
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
<<<<<<< HEAD
		//Update relative click position
		r_press.x = xyrel.x;
		r_press.y = xyrel.y;
=======
		//SDL_GetMouseState(&press.x, &press.y);
		press.x=xyrel.x;
		press.y=xyrel.y;
>>>>>>> origin/master
	}
	
	//Selection rect
	if (e->button.button == SDL_BUTTON_LEFT)
	{
		active = true;

		//X axis
		if (r_press.x > r_pos.x)
		{
			r_rect.x = r_pos.x;
			r_rect.w = r_press.x - r_pos.x;
		}
		else
		{
			r_rect.x = r_press.x;
			r_rect.w = r_pos.x - r_press.x;
		}

		//Y axis
		if (r_press.y > r_pos.y)
		{
			r_rect.y = r_pos.y;
			r_rect.h = r_press.y - r_pos.y;
		}
		else
		{
			r_rect.y = r_press.y;
			r_rect.h = r_pos.y - r_press.y;
		}

		rect_abs = r_rect;
	}

	//Mouse release
	if (e->type == SDL_MOUSEBUTTONUP)
	{
		active = false;
	}

	return active;
}


void Mouse::scroll(Camera &cam, Map map)
{
	//Scroll blocking while selecting
	if (active) return;

	//Scroll parameters
	int margin = 10;
	float speed = 5;

	//Absolute mouse position
	SDL_Point pos;
	SDL_GetMouseState(&pos.x, &pos.y);
	//cout << "Mouse: --  " << pos.x << " , " << pos.y << endl;
	
	///Lineal scrolling
	//Left
	if (pos.x < margin)
	{
		//Limit
		if (cam.getCen().x - speed <= 0)
			cam.setCen(0, cam.getCen().y);
		else
			cam.move(-speed, 0);
	}

	//Right
	if (pos.x > gWindow.getWidth() - margin)
	{
		//Limit
		if(cam.getCen().x + speed >= map.getSize().x)
			cam.setCen(map.getSize().x, cam.getCen().y);
		else
			cam.move(speed, 0);
	}

	if (cam.getCen().y >= 0)
	{
		//Up
		if (pos.y < margin)
		{
			//Limit
			if (cam.getCen().y - speed <= 0)
				cam.setCen(cam.getCen().x, 0);
			else
				cam.move(0, -speed);
		}
		//Down
		if (pos.y > gWindow.getHeight() - margin)
		{
			//Limit
			if (cam.getCen().y + speed >= map.getSize().y)
				cam.setCen(cam.getCen().x, map.getSize().y);
			else
				cam.move(0, speed);
		}
	}
	//cout << cam.getCen().x << " , " << cam.getCen().y << endl;
}


//Cursor and selection render
void Mouse::render(SDL_Renderer *renderer, SDL_Point posicion)
{
	//Cursor
	cursor->render(renderer, posicion.x, posicion.y, NULL);

	//Selection rect
	if (active) {
		if (r_press.y < r_pos.y)
			rect_abs.y = r_press.y + (posicion.y - r_pos.y);
		else
			rect_abs.y = posicion.y;
		//Render
		SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawRect(renderer, &rect_abs);
	}
}


SDL_Rect Mouse::getSel()
{
	return r_rect;
}