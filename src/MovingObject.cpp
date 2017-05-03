#include "MovingObject.h"


MovingObject::MovingObject(int type, int player):GameObject(type, player)
{
	//No rotation
	m_dir.x = 1;
	m_dir.y = 0;
	m_angle = 0;
	
	//No destination
	m_dest.x = cen.x;
	m_dest.y = cen.y;
	f_following = false;

	//Stopped
	m_vel.x = 0;
	m_vel.y = 0;

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
		if (((cen.x > m_sel.x - m_tex->getDim().x/2) && (cen.x < (m_sel.x + m_sel.w + m_tex->getDim().x / 2))))
		{
			if (((cen.y > m_sel.y - m_tex->getDim().y / 2) && (cen.y < (m_sel.y + m_sel.h + m_tex->getDim().y / 2))))
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
}

void MovingObject::stop()
{
	m_dest.x = cen.x;
	m_dest.y = cen.y;
	m_vel.x = 0;
	m_vel.y = 0;
}

void MovingObject::moveStraight(int x, int y)
{

	m_dest.x = x;
	m_dest.y = y;
	m_dir.x = m_dest.x - cen.x;
	m_dir.y = m_dest.y - cen.y;
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

//Velocidad
Vector2 MovingObject::GetVel()
{
	return m_vel;
}

void MovingObject::SetVel(float x, float y)
{
	m_vel.x = x;
	m_vel.y = y;
}

void MovingObject::SetMaxVel(float v)
{
	max_vel = v;
}
//Dirección
Vector2 MovingObject::GetDir()
{
	return m_dir;
}

void MovingObject::SetDir(float x, float y)
{
	m_dir.x = x;
	m_dir.y = y;
}

void MovingObject::setDest(float x, float y)
{
	//Destino
	m_dest.x = x;
	m_dest.y = y;
}

bool MovingObject::onPoint(Vector2 p)
{
	if (cen.distance(p) < max_vel) return true;
	else return false;
}

bool MovingObject::onDest()
{
	return onPoint(m_dest);
}