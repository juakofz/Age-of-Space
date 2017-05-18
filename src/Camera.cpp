#include "Camera.h"

Camera::Camera()
{
	m_cen.x = m_cen.y = 0.0f;
	m_frame.w = m_frame.h = m_frame.x = m_frame.y = 0;
	m_zoom = 1;

	f_up = f_down = f_left = f_right = false;
}


Camera::~Camera()
{
}

void Camera::scroll()
{
	int scroll = 10;
	if (g_keyboardState != NULL)
	{
		if (g_keyboardState[SDL_SCANCODE_UP])
			setCen(m_cen.x, m_cen.y - scroll);

		if (g_keyboardState[SDL_SCANCODE_DOWN])
			setCen(m_cen.x, m_cen.y + scroll);

		if (g_keyboardState[SDL_SCANCODE_LEFT])
			setCen(m_cen.x - scroll, m_cen.y);

		if (g_keyboardState[SDL_SCANCODE_RIGHT])
			setCen(m_cen.x + scroll, m_cen.y);
	}	

}

void Camera::update(ViewPort v)
{
	m_frame.w = v.getParam().w;
	m_frame.h = v.getParam().h;

	setCen(m_cen.x, m_cen.y);
	//cout << "Update" << endl;
}


//Movimiento y zoom
void Camera::move(float mx, float my)
{
	m_cen.x += mx;
	m_cen.y += my;

	m_frame.x += mx;
	m_frame.y += my;
}

void Camera::changeZoom(float z)
{
	m_zoom += z;
}

//Margen de renderizado
bool Camera::isVisible(Vector2 pos, int margin)
{
	if ((pos.x + margin >= m_frame.x) && (pos.x - margin <= m_frame.x + m_frame.w))
	{
		if ((pos.y + margin >= m_frame.y) && (pos.y - margin <= m_frame.y + m_frame.h))
			return true;
	}
	return false;
}

//Posición
SDL_Point Camera::getPos()
{
	SDL_Point temp{ m_frame.x, m_frame.y };
	return temp;
}

void Camera::setPos(float x, float y)
{
	m_frame.x = x;
	m_frame.y = y;

	m_cen.x = m_frame.x + m_frame.w / 2;
	m_cen.y = m_frame.y + m_frame.h / 2;
}

//Centro
Vector2 Camera::getCen()
{
	return m_cen;
}

void Camera::setCen(float x, float y)
{
	m_cen.x = x;
	m_cen.y = y;

	m_frame.x = m_cen.x - m_frame.w / 2;
	m_frame.y = m_cen.y - m_frame.h / 2;
}

//Tamaño
void Camera::setSize(int w, int h)
{
	m_frame.w = w;
	m_frame.h = h;

	m_frame.x = m_cen.x - m_frame.w / 2;
	m_frame.y = m_cen.y - m_frame.h / 2;
}

Vector2 Camera::getSize()
{
	Vector2 temp;
	temp.x = m_frame.w;
	temp.y = m_frame.h;
	return temp;
}