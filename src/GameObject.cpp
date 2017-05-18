#include "GameObject.h"

GameObject::GameObject(int type, int player):m_type(type)
{
	m_selectable = true;
	m_player = player;
}

GameObject::GameObject(int type):m_type(type)
{
	m_selectable = false;
	m_player = 0;
}

GameObject::~GameObject()
{
}

void GameObject::select()
{
	if(m_selectable)
	{
		f_sel = true;
		m_sel_angle = 0;
	}
}

void GameObject::deselect()
{
	if(m_selectable) f_sel = false;
}

void GameObject::render(Camera cam)
{
	//If inside camera frame
	if (cam.isVisible(getCen(), m_size/2))
	{
		SDL_Point center;
		center.x = m_cen.x - cam.getPos().x;
		center.y = m_cen.y - cam.getPos().y;
		m_tex->render(g_Renderer, &center, m_width, m_height, NULL, m_angle); //Render object texture

		//Selection marker
		if(m_selectable && f_sel)
		{
			m_marker->render(g_Renderer, &center, m_size * 1.2f, m_size * 1.2f, NULL, m_sel_angle);
			//Marker rotation
			if (m_sel_angle > 360) m_sel_angle = 0;
			else m_sel_angle++;
		}
	}
}

Vector2 GameObject::getPos()
{
	return m_pos;
}

void GameObject::setPos(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
	m_cen.x = m_pos.x + m_tex->getDim().x / 2;
	m_cen.y = m_pos.y + m_tex->getDim().y / 2;
}

void GameObject::setPos(Vector2 p)
{
	m_pos.x = p.x;
	m_pos.y = p.y;
	m_cen.x = m_pos.x + m_tex->getDim().x / 2;
	m_cen.y = m_pos.y + m_tex->getDim().y / 2;
}

Vector2 GameObject::getCen()
{
	return m_cen;
}

void GameObject::setCen(float x, float y)
{
	m_cen.x = x;
	m_cen.y = y;
	m_pos.x = m_cen.x - m_tex->getDim().x / 2;
	m_pos.y = m_cen.y - m_tex->getDim().y / 2;
}

void GameObject::setCen(Vector2 c)
{
	m_cen.x = c.x;
	m_cen.y = c.y;
	m_pos.x = m_cen.x - m_tex->getDim().x / 2;
	m_pos.y = m_cen.y - m_tex->getDim().y / 2;
}

//void GameObject::giveCen(Vector2 &dest)
//{
//	dest = cen;
//}

void GameObject::setTex(Texture *t)
{
	m_tex = t;
	m_width = t->getDim().x;
	m_height = t->getDim().y;
	m_size = t->getDiag();
}

void GameObject::setMarker(Texture *t)
{
	m_marker = t;
}

bool GameObject::getSel()
{
	return f_sel;
}

bool GameObject::isInside(SDL_Rect rect)
{
	if (((m_cen.x > rect.x - m_tex->getDim().x / 2) && (m_cen.x < (rect.x + rect.w + m_tex->getDim().x / 2))))
	{
		if (((m_cen.y > rect.y - m_tex->getDim().y / 2) && (m_cen.y < (rect.y + rect.h + m_tex->getDim().y / 2))))
		{
			return true;
		}
		else return false;
	}
	return false;
}

bool GameObject::clickOn(SDL_Point mouse)
{
	if (mouse.x >= m_pos.x && mouse.x <= m_pos.x + m_width) //x axis
	{
		if (mouse.y >= m_pos.y && mouse.y <= m_pos.y + m_height) //y axis
		{
			return true;
		}
	}
	return false;
}

void GameObject::scaleTo(int s)
{
	m_size = s;
	float scale = s / m_tex->getDiag();
	m_width = m_tex->getDim().x * scale;
	m_height = m_tex->getDim().y * scale;
}

int GameObject::getSize()
{
	return m_size;
}

Vector2 GameObject::getDim()
{
	return m_tex->getDim();
}

int GameObject::getType()
{
	return m_type;
}

void GameObject::setPlayer(int p)
{
	m_player = p;
}

int GameObject::getPlayer()
{
	return m_player;
}


void GameObject::setHealth(float h)
{
	if (h < 0) h = 0;
	m_health = h;
}

float GameObject::getHealth()
{
	return m_health;
}

bool GameObject::damage(float d)
{
	if (d < 0) d = 0;
	m_health -= d;
	if (m_health < 0)
		return true;
	else
		return false;
}