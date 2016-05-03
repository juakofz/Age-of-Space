#pragma once
#include "Texture.h"

extern SDL_Renderer* gRenderer;

class Map
{

public:
	Map();
	~Map();

	void setMap(Texture *m);
	void setBackground(Texture *b);

	//Render map
	void render(SDL_Rect camera);


private:
	Texture * map, * background;

	Vector2 size;
};

