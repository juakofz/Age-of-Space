#include "ScreenArea.h"


ScreenArea::ScreenArea(void)
{
}


ScreenArea::~ScreenArea(void)
{

}

void ScreenArea::render()
{
	viewport.render();
}

int ScreenArea::event(SDL_Event* e, SDL_Point xyrel)
{
	return 1;
}

void ScreenArea::Open()
{
	cout<<"mal abierto"<<endl;
}
//Funciones para los viewports
void ScreenArea::initViewPort(SDL_Rect rect, std::string path)
{
	viewport.Init(rect.x, rect.y, rect.w, rect.h, path);
}

void ScreenArea::initViewPort(float x1, float y1, float x2, float y2, std::string path)
{
	float x1_screen = x1 * g_SCREEN_WIDTH;
	float x2_screen = x2 * g_SCREEN_WIDTH;
	float y1_screen = y1 * g_SCREEN_HEIGHT;
	float y2_screen = y2 * g_SCREEN_HEIGHT;
	viewport.Init(x1_screen, y1_screen, x2_screen - x1_screen, y2_screen - y1_screen, path);
	viewport.SetRel(x1, y1, x2 - x1, y2 - y1);
}

void ScreenArea::SetRel(float x, float y, float w, float h)
{
	viewport.SetRel(x, y, w, h);
}

void ScreenArea::update()
{
	viewport.ActParam();
}


void ScreenArea::renderViewport()
{
	viewport.render();
}

int ScreenArea::up()
{
	return viewport.getParam().y;
}

int ScreenArea::down()
{
	return (viewport.getParam().y + viewport.getParam().h);
}

int ScreenArea::left()
{
	return viewport.getParam().x;
}

int ScreenArea::right()
{
	return (viewport.getParam().x + viewport.getParam().w);
}


int ScreenArea::getHeight()
{
	return viewport.getHeight();
}

int ScreenArea::getWidth()
{
	return viewport.getWidth();
}

ViewPort ScreenArea::getViewport()
{
	return viewport;
}

SDL_Point ScreenArea::relatxy()
{
	return viewport.relatxy();
}

SDL_Point ScreenArea::relatxy(int x, int y)
{
	return viewport.relatxy(x, y);
}

void ScreenArea::Set()
{
	viewport.Set();
}