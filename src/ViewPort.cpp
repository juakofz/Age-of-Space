#include "ViewPort.h"


ViewPort::ViewPort(void)
{
	param.x=param.y=param.h=param.w=0;

}


ViewPort::~ViewPort(void)
{
}

//parametros
void ViewPort::SetParam(int x, int y, int w, int h)
{
	param.x=x;
	param.y=y;
	param.h=h;
	param.w=w;
}


//renderizar
void ViewPort::render()
{
	SDL_RenderSetViewport( gRenderer, &param );
				
	//Render texture to screen
	SDL_RenderCopy( gRenderer, tex.texture, NULL, NULL );
}
SDL_Rect ViewPort::GetParam()
{
	 return param;
}
void ViewPort::Init(int x, int y, int w, int h, std::string path)
{
	param.x=x;
	param.y=y;
	param.h=h;
	param.w=w;
	tex.load(path, gRenderer);
}