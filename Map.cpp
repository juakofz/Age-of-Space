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
	//Scroll factor. Effective background size = size / scroll factor
	float scroll = 0.3;

	SDL_Rect clip;
	clip.w = cam.getSize().x;
	clip.h = cam.getSize().y;
	clip.x = scroll * cam.getPos().x + (background->getDim().x - clip.w) / 2;
	clip.y = scroll * cam.getPos().y + (background->getDim().y - clip.h) / 2;

	SDL_Point center;
	center.x = cam.getSize().x / 2;
	center.y = cam.getSize().y / 2;

	//render(SDL_Renderer* renderer, SDL_Point* center, int w, int h, SDL_Rect* clip, double angle, SDL_RendererFlip flip)
	background->render(gRenderer, &center, cam.getSize().x, cam.getSize().y, &clip);
}

void Map::renderGrid(Camera cam)
{
	int margin_x = grid->getDim().x / 2;
	int margin_y = grid->getDim().y / 2;

	//Grid matrix
	for (int i = + margin_x; i <= size.x - margin_x; i = i + grid->getDim().x)
	{
		for (int j = + margin_y; j <= size.y - margin_y; j = j + grid->getDim().y)
		{

			Vector2 gpos;
			gpos.x = i;
			gpos.y = j;

			//Check for visibility
			if (cam.isVisible(gpos, margin_x))
			{
				SDL_Point center;
				center.x = i - cam.getPos().x;
				center.y = j - cam.getPos().y;
				grid->render(gRenderer, &center, grid->getDim().x, grid->getDim().y);
			}
		}
	}
}
