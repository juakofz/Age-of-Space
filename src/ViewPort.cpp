#include "ViewPort.h"


ViewPort::ViewPort(void)
{
	param.x = param.y = param.h = param.w = 0;

}


ViewPort::~ViewPort(void)
{
}

//parametros
void ViewPort::SetParam(int w, int h, int x, int y)
{
	param.w = w;
	param.h = h;
	
	param.x = x;
	param.y = y;
}

void ViewPort::ActParam()
{
	param.x = g_Window.getWidth() * origen.x;
	param.y = g_Window.getHeight() * origen.y;
	tamañofin.x = param.w = g_Window.getWidth() * tamaño.x;
	tamañofin.y = param.h = g_Window.getHeight() * tamaño.y;

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
	SDL_RenderSetViewport( g_Renderer, &param );	

	//Render texture to screen
	tex.render(g_Renderer, &tamañofin);
}

SDL_Rect ViewPort::GetParam()
{
	 return param;
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
	return param.y;
}


void ViewPort::Init(int x, int y, int w, int h, std::string path)
{
	param.x = x;
	param.y = y;
	param.h = h;
	param.w = w;
	tex.load(path, g_Renderer);
}

void ViewPort::Set()
{
	SDL_RenderSetViewport( g_Renderer, &param );	
}


//Returns mouse position relative to viewport
SDL_Point ViewPort::relatxy()
{
	SDL_Point xyrel;
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	xyrel.x = mx - param.x;
	xyrel.y = my - param.y;
	return xyrel;
}

SDL_Point ViewPort::relatxy(int x, int y)
{
	SDL_Point xyrel;
	xyrel.x = x - param.x;
	xyrel.y = y - param.y;
	return xyrel;
}