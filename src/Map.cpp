#include "Map.h"



Map::Map()
{
}

Map::Map(float width, float height, Texture *bg, Texture *gr)
{
	size.x = width;
	size.y = height;
	background = bg;
	grid = gr;
}

Map::~Map()
{
}


//Size
void Map::setSize(float x, float y)
{
	size.x = x;
	size.y = y;
}

Vector2 Map::getSize()
{
	return size;
}

//Textures
void Map::setBg(Texture *bg)
{
	background = bg;
}

void Map::setGrid(Texture *gr)
{
	grid = gr;
}

//Render
void Map::renderBg(Camera cam)
{
	SDL_Rect clip;
	clip.w = cam.getSize().x;
	clip.h = cam.getSize().y;
	clip.x = cam.getPos().x;
	clip.y = cam.getPos().y;

	SDL_Point cero;
	cero.x = 0;
	cero.y = 0;

	//render(SDL_Renderer* renderer, SDL_Point* center, int w, int h, SDL_Rect* clip, double angle, SDL_RendererFlip flip)
	background->render(gRenderer, &cero, cam.getSize().x, cam.getSize().y, &clip);
}
void renderParallax(Camera cam);
