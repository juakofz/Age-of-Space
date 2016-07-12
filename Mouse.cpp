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

void Mouse::update(SDL_Event *e, bool sel)
{
	//Click event
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		//Update relative click position to current position
		r_press.x = r_pos.x;
		r_press.y = r_pos.y;

		//Update absolute click position
		press.x = pos.x;
		press.y = pos.y;

		//Update map click position
		m_press.x = m_pos.x;
		m_press.y = m_pos.y;
	}

	//Selection rect
	if (sel && e->button.button == SDL_BUTTON_LEFT)
	{
		//Selection flag
		active = true;

		//Reclangle correction
		//X axis
		if (r_press.x > r_pos.x)
		{
			//Relative
			r_rect.x = r_pos.x;
			r_rect.w = r_press.x - r_pos.x;

			//Absolute
			rect.x = pos.x;
			rect.w = press.x - pos.x;

			//Map
			m_rect.x = m_pos.x;
			m_rect.w = m_press.x - m_pos.x;
		}
		else
		{
			//Relative
			r_rect.x = r_press.x;
			r_rect.w = r_pos.x - r_press.x;

			//Absolute
			rect.x = press.x;
			rect.w = pos.x - press.x;

			//Relative
			m_rect.x = m_press.x;
			m_rect.w = m_pos.x - m_press.x;
		}
		//Y axis
		if (r_press.y > r_pos.y)
		{
			//Relative
			r_rect.y = r_pos.y;
			r_rect.h = r_press.y - r_pos.y;

			//Absolute
			rect.y = pos.y;
			rect.h = press.y - pos.y;

			//Relative
			m_rect.y = m_pos.y;
			m_rect.h = m_press.y - m_pos.y;
		}
		else
		{
			//Relative
			r_rect.y = r_press.y;
			r_rect.h = r_pos.y - r_press.y;

			//Absolute
			rect.y = press.y;
			rect.h = pos.y - press.y;

			//Relative
			m_rect.y = m_press.y;
			m_rect.h = m_pos.y - m_press.y;
		}
	}

	//Mouse release
	if (e->type == SDL_MOUSEBUTTONUP)
	{
		active = false;
	}
}



void Mouse::scroll(Camera &cam, Map map)
{
	//Scroll blocking while selecting
	if (active) return;

	//Scroll parameters
	int margin = 10;
	float speed = 5;

	//Lineal scrolling
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
void Mouse::render(SDL_Renderer *renderer)
{
	//Cursor
	cursor->render(renderer, pos.x, pos.y);

	//Selection rect
	if (active) {
		SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawRect(renderer, &rect);
	}
}

//Return relative selection rect
SDL_Rect Mouse::getSel()
{
	return r_rect;
}


//Set absolute position
void Mouse::setPos(int px, int py)
{
	pos.x = px;
	pos.y = py;
}

//Get absolute position
SDL_Point Mouse::getPos()
{
	return pos;
}

//Set relative position
void Mouse::setR_pos(int px, int py)
{
	r_pos.x = px;
	r_pos.y = py;
}


//Get relative position
SDL_Point Mouse::getR_pos()
{
	return r_pos;
}

//Is mouse selecting
bool Mouse::isActive()
{
	return active;
}


//Set relative position
void Mouse::setMpos(int px, int py)
{
	m_pos.x = px;
	m_pos.y = py;
}

//Get map position
SDL_Point Mouse::getMpos()
{
	return m_pos;
}

//Return map selection rect
SDL_Rect Mouse::getMrect()
{
	return m_rect;
}
