#include "ZonaPantalla.h"


ZonaPantalla::ZonaPantalla(void)
{
}


ZonaPantalla::~ZonaPantalla(void)
{

}

void ZonaPantalla::render()
{
	viewport.render();
}

int ZonaPantalla::event(SDL_Event* e, SDL_Point xyrel)
{
	return 1;
}

void ZonaPantalla::Open()
{
	cout<<"mal abierto"<<endl;
}
//Funciones para los viewports
void ZonaPantalla::initViewport(int x, int y, int w, int h,std::string path)
{
	viewport.Init(x, y, w, h, path);
}

void ZonaPantalla::SetRel(float x, float y, float w, float h)
{
	viewport.SetRel(x, y, w, h);
}

void ZonaPantalla::ActParam()
{
	viewport.ActParam();
}


void ZonaPantalla::renderViewport()
{
	viewport.render();
}

int ZonaPantalla::getY()
{
	return viewport.getY();
}

int ZonaPantalla::getHeight()
{
	return viewport.getHeight();
}

ViewPort ZonaPantalla::getViewport()
{
	return viewport;
}

SDL_Point ZonaPantalla::relatxy()
{
	return viewport.relatxy();
}
SDL_Point ZonaPantalla::relatxy(int x, int y)
{
	return viewport.relatxy(x, y);
}

void ZonaPantalla::Set()
{
	viewport.Set();
}