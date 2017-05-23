#include "MovingObject.h"


MovingObject::MovingObject(int type, int player):GameObject(type, player)
{
	//No rotation
	m_dir.x = 1;
	m_dir.y = 0;
	m_angle = 0;
	
	//No destination
	m_dest.x = m_cen.x;
	m_dest.y = m_cen.y;

	//Stopped
	m_vel.x = 0;
	m_vel.y = 0;
	m_accel.x = 0;
	m_accel.y = 0;

	f_sel = false;
	m_sel_angle = 0;

	m_tex = NULL;
}

MovingObject::~MovingObject()
{
}

int MovingObject::event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m)
{
	//Selection (box)
	if (e->button.button == SDL_BUTTON_LEFT)
	{
		if (((m_cen.x > m_sel.x - m_tex->getDim().x/2) && (m_cen.x < (m_sel.x + m_sel.w + m_tex->getDim().x / 2))))
		{
			if (((m_cen.y > m_sel.y - m_tex->getDim().y / 2) && (m_cen.y < (m_sel.y + m_sel.h + m_tex->getDim().y / 2))))
			{
				select();
			}
			else deselect();
		}
		else deselect();
	}

	//Right click: set destination
	if ((e->type == SDL_MOUSEBUTTONDOWN) && (e->button.button == SDL_BUTTON_RIGHT) && (f_sel))
	{
		m_dest.x = m.x;
		m_dest.y = m.y;
	}
	return 0;
}

void MovingObject::render(Camera cam)
{
	GameObject::render(cam);
	if (g_f_debug) renderDebug(cam);
}

void MovingObject::renderDebug(Camera cam)
{
	//If inside camera frame
	if (cam.isVisible(getCen(), m_size / 2))
	{
		SDL_Point center;
		center.x = m_cen.x - cam.getPos().x;
		center.y = m_cen.y - cam.getPos().y;

		SDL_Point dest;
		dest.x = m_dest.x - cam.getPos().x;
		dest.y = m_dest.y - cam.getPos().y;
		
		float max_length = 100.0f;

		//Velocity (red line)
		float aux_length;

		if (m_vel.length() * 20 < max_length)
			aux_length = m_vel.length() * 20;
		else
			aux_length = max_length;

		Vector2 vel_debug = m_vel.normalize(aux_length);

		SDL_SetRenderDrawColor(g_Renderer, 255, 0, 0, 150);
		SDL_RenderDrawLine(g_Renderer, center.x, center.y,
							center.x + vel_debug.x, center.y + vel_debug.y);

		//Acceleration (blue line)
		if (m_accel.length() < 10.0f)
		{
			SDL_SetRenderDrawColor(g_Renderer, 0, 0, 255, 150);
			Vector2 accel_debug = m_accel.normalize(m_accel.length() * 100);
			SDL_RenderDrawLine(g_Renderer, center.x, center.y,
							   center.x + accel_debug.x, center.y + accel_debug.y);
		}

		//Direction (green line)
		SDL_SetRenderDrawColor(g_Renderer, 0, 255, 0, 150);
		Vector2 debug_dir = m_dir.normalize(20.0f);
		SDL_RenderDrawLine(g_Renderer, center.x, center.y,
						center.x + debug_dir.x, center.y + debug_dir.y);

		//Direction normal (cyan line)
		SDL_SetRenderDrawColor(g_Renderer, 0, 255, 255, 150);
		Vector2 normal = debug_dir.normal();
		SDL_RenderDrawLine(g_Renderer, center.x, center.y,
			center.x + normal.x, center.y + normal.y);

		//Destination (red cross)
		SDL_SetRenderDrawColor(g_Renderer, 255, 0, 0, 150);
		int cross_size = 4;
		SDL_RenderDrawLine(g_Renderer, dest.x - cross_size, dest.y - cross_size,
			dest.x + cross_size, dest.y + cross_size);
		SDL_RenderDrawLine(g_Renderer, dest.x + cross_size, dest.y - cross_size,
			dest.x - cross_size, dest.y + cross_size);
	}
}

bool MovingObject::move()
{
	setCen(m_cen + m_vel); //Just move straight
	return false;
}

void MovingObject::stop()
{
	setDest(m_cen);
	m_vel.x = 0;
	m_vel.y = 0;
	m_accel.x = 0;
	m_accel.y = 0;
}

void MovingObject::moveStraight(int x, int y)
{

	m_dest.x = x;
	m_dest.y = y;
	m_dir.x = m_dest.x - m_cen.x;
	m_dir.y = m_dest.y - m_cen.y;
	m_angle = (180 * atan2(m_dir.y, m_dir.x) / M_PI);

	m_accel = m_dir.normalize(m_max_accel);
	m_vel += m_accel;
	m_pos += m_vel;
	m_vel *= m_friction;
}

Vector2 MovingObject::getDest()
{
	return m_dest;
}

Vector2 MovingObject::getVel()
{
	return m_vel;
}

void MovingObject::setVel(float x, float y)
{
	m_vel.x = x;
	m_vel.y = y;
}

void MovingObject::setVel(Vector2 vel)
{
	m_vel = vel;
}

void MovingObject::addVel(Vector2 vel)
{
	m_vel += vel;
}

float MovingObject::getSpeed()
{
	return m_speed;
}

void MovingObject::setSpeed(float s)
{
	m_speed = s;
}

Vector2 MovingObject::getDir()
{
	return m_dir;
}

void MovingObject::setDir(float x, float y)
{
	m_dir.x = x;
	m_dir.y = y;
	Vector2 aux(x, y);
	m_angle = aux.angle();
}

void MovingObject::setDir(Vector2 dir)
{
	m_dir = dir;
	m_angle = dir.angle();
}


float MovingObject::getAngle()
{
	return m_angle;
}

void MovingObject::setAngle(float a)
{
	m_angle = a;
	m_dir = Vector2::toVector(a);
}

void MovingObject::setDest(float x, float y)
{
	//Destino
	m_dest.x = x;
	m_dest.y = y;
}

void MovingObject::setDest(Vector2 dest)
{
	//Destino
	m_dest = dest;
}

bool MovingObject::onPoint(Vector2 p)
{
	if (m_cen.distance(p) < m_size/5) return true;
	else return false;
}

bool MovingObject::onDest()
{
	return onPoint(m_dest);
}