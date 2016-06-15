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
	param.x = gWindow.getWidth() * origen.x;
	param.y = gWindow.getHeight() * origen.y;
	tama�ofin.x = param.w = gWindow.getWidth() * tama�o.x;
	tama�ofin.y = param.h = gWindow.getHeight() * tama�o.y;

}


void ViewPort::SetRel(float x, float y, float w, float h)
{
	origen.x = x;
	origen.y = y;

	tama�o.x = w;
	tama�o.y = h;

}

//renderizar
void ViewPort::render()
{
	//renderizamos en el viewport seleccionado
	SDL_RenderSetViewport( gRenderer, &param );	

	//Render texture to screen
	tex.render(gRenderer, &tama�ofin);
}

SDL_Rect ViewPort::GetParam()
{
	 return param;
}

int ViewPort::getHeight()
{
	return tama�ofin.y;
}

int ViewPort::getWidth()
{
	return tama�ofin.x;
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
	tex.load(path, gRenderer);
}

void ViewPort::Set()
{
	SDL_RenderSetViewport( gRenderer, &param );	
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