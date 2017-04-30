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

void Mouse::update(SDL_Event *e, int area,  bool sel)
{
	if (sel && (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP))
	{
		//Check if left button is being pressed
		if (e->button.state == SDL_PRESSED) f_active = true;
		else f_active = false;
	}
	
	//Click event
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		//Update relative click position to current position
		m_viewport_press.x = m_viewport_pos.x;
		m_viewport_press.y = m_viewport_pos.y;

		//Update absolute click position
		press.x = pos.x;
		press.y = pos.y;

		//Update map click position
		m_map_press.x = m_map_pos.x;
		m_map_press.y = m_map_pos.y;
	}

	//Selection rect
	if (sel && e->button.button == SDL_BUTTON_LEFT)
	{

		//Reclangle correction
		//X axis
		if (m_viewport_press.x > m_viewport_pos.x)
		{
			//Relative
			m_viewport_rect.x = m_viewport_pos.x;
			m_viewport_rect.w = m_viewport_press.x - m_viewport_pos.x;

			//Absolute
			rect.x = pos.x;
			rect.w = press.x - pos.x;

			//Map
			m__map_rect.x = m_map_pos.x;
			m__map_rect.w = m_map_press.x - m_map_pos.x;
		}
		else
		{
			//Relative
			m_viewport_rect.x = m_viewport_press.x;
			m_viewport_rect.w = m_viewport_pos.x - m_viewport_press.x;

			//Absolute
			rect.x = press.x;
			rect.w = pos.x - press.x;

			//Relative
			m__map_rect.x = m_map_press.x;
			m__map_rect.w = m_map_pos.x - m_map_press.x;
		}
		//Y axis
		if (m_viewport_press.y > m_viewport_pos.y)
		{
			//Relative
			m_viewport_rect.y = m_viewport_pos.y;
			m_viewport_rect.h = m_viewport_press.y - m_viewport_pos.y;

			//Absolute
			rect.y = pos.y;
			rect.h = press.y - pos.y;

			//Relative
			m__map_rect.y = m_map_pos.y;
			m__map_rect.h = m_map_press.y - m_map_pos.y;
		}
		else
		{
			//Relative
			m_viewport_rect.y = m_viewport_press.y;
			m_viewport_rect.h = m_viewport_pos.y - m_viewport_press.y;

			//Absolute
			rect.y = press.y;
			rect.h = pos.y - press.y;

			//Relative
			m__map_rect.y = m_map_press.y;
			m__map_rect.h = m_map_pos.y - m_map_press.y;
		}
	}
}



void Mouse::scroll(Camera &cam, Map map)
{
	//Scroll blocking while selecting
	if (f_active) return;

	//Scroll parameters
	int margin = 15;
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
	if (pos.x > g_Window.getWidth() - margin)
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
		if (pos.y > g_Window.getHeight() - margin)
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
	if (f_active) {
		SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawRect(renderer, &rect);
	}
}

//Return relative selection rect
SDL_Rect Mouse::getSel()
{
	return m_viewport_rect;
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
	m_viewport_pos.x = px;
	m_viewport_pos.y = py;
}


//Get relative position
SDL_Point Mouse::getR_pos()
{
	return m_viewport_pos;
}

//Is mouse selecting
bool Mouse::isActive()
{
	return f_active;
}


//Set relative position
void Mouse::setMpos(int px, int py)
{
	m_map_pos.x = px;
	m_map_pos.y = py;
}

//Get map position
SDL_Point Mouse::getMpos()
{
	return m_map_pos;
}

//Return map selection rect
SDL_Rect Mouse::getMrect()
{
	return m__map_rect;
}
