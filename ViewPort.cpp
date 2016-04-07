#include "ViewPort.h"


ViewPort::ViewPort(void)
{
	param.x=param.y=param.h=param.w=0;

}


ViewPort::~ViewPort(void)
{
}

//parametros
void ViewPort::SetParam(int w, int h, int x, int y)
{
	param.x=x;
	param.y=y;
	param.h=h;
	param.w=w;
}

void ViewPort::SetRel(float x, float y, float w, float h)
{
	origen.x=x;
	origen.y=y;
	tamaño.x=w;
	tamaño.y=h;

}
void ViewPort::ActParam()
{
	param.x=gWindow.getWidth()*origen.x;
	param.y=gWindow.getHeight()*origen.y;
	tamañofin.x=param.w=gWindow.getWidth()*tamaño.x;
	tamañofin.y=param.h=gWindow.getHeight()*tamaño.y;
	printf("nuevos param %d %d %d %d\n", param.x, param.y, param.w, param.h);

}
//renderizar
void ViewPort::render()
{

	SDL_RenderSetViewport( gRenderer, &param );				
	//Render texture to screen
	tex.render(gRenderer,&tamañofin);
	//ast.render();
}
SDL_Rect ViewPort::GetParam()
{
	 return param;
}

int ViewPort::getHeight()
{
	return tamañofin.y;
}

int ViewPort::getY()
{
	return param.y;
}


void ViewPort::Init(int x, int y, int w, int h, std::string path)
{
	param.x=x;
	param.y=y;
	param.h=h;
	param.w=w;
	tex.load(path, gRenderer);
	ast.SetCen(50,50);
	ast.tex.load("asteroide.png", gRenderer);
}

void ViewPort::Set()
{
	SDL_RenderSetViewport( gRenderer, &param );	
}


SDL_Point ViewPort::relatxy()
{
	SDL_Point xyrel;
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	xyrel.x=mx-param.x;
	xyrel.y=my-param.y;
	return xyrel;
}

void ViewPort::event(SDL_Event* e)
{

	ast.event(e, relatxy());
}