#include "Map.h"



Map::Map()
{
}

Map::~Map()
{
}

void Map::setMap(Texture *m)
{
	map = m;
}

void Map::setBackground(Texture *b)
{
	background = b;
}


void Map::render(SDL_Rect camera)
{
	SDL_Point center;
	center.x = camera.w / 2;
	center.y = camera.h / 2;

	SDL_Rect clip = camera;
	//Background
	background->render(gRenderer, &center, camera.w, camera.h, &camera);
	//render(SDL_Renderer* renderer, SDL_Point* center, int w, int h, SDL_Rect* clip = NULL, double angle  = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);

}

