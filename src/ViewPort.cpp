#include "ViewPort.h"


ViewPort::ViewPort()
{
	m_param.x = m_param.y = m_param.h = m_param.w = 0;
}

ViewPort::ViewPort(SDL_Rect rect)
{
	m_param = rect;
}


ViewPort::~ViewPort()
{
}

void ViewPort::Init(int x, int y, int w, int h, std::string path)
{
	m_param.x = x;
	m_param.y = y;
	m_param.h = h;
	m_param.w = w;
	m_tex.load(path, g_Renderer);
}

void ViewPort::SetParam(int w, int h, int x, int y)
{
	m_param.w = w;
	m_param.h = h;
	m_param.x = x;
	m_param.y = y;
}

void ViewPort::ActParam()
{
	m_param.x = g_Window.getWidth() * origen.x;
	m_param.y = g_Window.getHeight() * origen.y;
	tamañofin.x = m_param.w = g_Window.getWidth() * tamaño.x;
	tamañofin.y = m_param.h = g_Window.getHeight() * tamaño.y;
}


void ViewPort::SetRel(float x, float y, float w, float h)
{
	origen.x = x;
	origen.y = y;

	tamaño.x = w;
	tamaño.y = h;

}

//renderizar
void ViewPort::render()
{
	//renderizamos en el viewport seleccionado
	SDL_RenderSetViewport( g_Renderer, &m_param );	

	//Render texture to screen
	m_tex.render(g_Renderer, &tamañofin);
}

SDL_Rect ViewPort::getParam()
{
	 return m_param;
}

int ViewPort::getHeight()
{
	return tamañofin.y;
}

int ViewPort::getWidth()
{
	return tamañofin.x;
}

int ViewPort::getY()
{
	return m_param.y;
}

void ViewPort::Set()
{
	SDL_RenderSetViewport( g_Renderer, &m_param );	
}

//Returns mouse position relative to viewport
SDL_Point ViewPort::relatxy()
{
	SDL_Point xyrel;
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	xyrel.x = mx - m_param.x;
	xyrel.y = my - m_param.y;
	return xyrel;
}

SDL_Point ViewPort::relatxy(int x, int y)
{
	SDL_Point xyrel;
	xyrel.x = x - m_param.x;
	xyrel.y = y - m_param.y;
	return xyrel;
}