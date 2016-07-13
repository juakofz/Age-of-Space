#include "Marker.h"

Marker::Marker(/*SDL_Point c, int h, int w, SDL_Color cl*/)
{
/*	color = cl;
	center = c;
	height = h;
	width = w;

	update();
*/
}

Marker::~Marker()
{
}

void Marker::draw(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	
	float scale = 0.2;

	SDL_RenderDrawLine(renderer, top_right.x, top_right.y, top_right.x - width*scale, top_right.y);
	SDL_RenderDrawLine(renderer, top_right.x, top_right.y, top_right.x, top_right.y + height*scale);

	SDL_RenderDrawLine(renderer, top_left.x, top_left.y, top_left.x + width*scale, top_right.y);
	SDL_RenderDrawLine(renderer, top_left.x, top_left.y, top_left.x, top_right.y + height*scale);

	SDL_RenderDrawLine(renderer, bottom_right.x, bottom_right.y, bottom_right.x - width*scale, bottom_right.y);
	SDL_RenderDrawLine(renderer, bottom_right.x, bottom_right.y, bottom_right.x, bottom_right.y - height*scale);

	SDL_RenderDrawLine(renderer, bottom_left.x, bottom_left.y, bottom_left.x + width*scale, bottom_left.y);
	SDL_RenderDrawLine(renderer, bottom_left.x, bottom_left.y, bottom_left.x, bottom_left.y - height*scale);
}
void Marker::setCen(SDL_Point c)
{
	center = c;

	update();
}

void Marker::setSize(int h, int w)
{
	height = h;
	width = w;
	
	update();
}

void Marker::setColor(SDL_Color cl)
{
	color = cl;
}

void Marker::update ()
{
	top_left.x = bottom_left.x = center.x - width / 2;
	top_right.x = bottom_right.x = center.x + width / 2;
	top_left.y = top_right.y = center.y - height / 2;
	bottom_left.y = bottom_right.y = center.y + height / 2;
}