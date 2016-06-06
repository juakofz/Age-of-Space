#pragma once
#include "Texture.h"
#include "Camera.h"

class Camera;

class Map
{
public:
	Map();
	Map(float width, float height, Texture *bg, Texture *gr);
	~Map();

	//Size
	void setSize(float x, float y);
	Vector2 getSize();

	//Textures
	void setBg(Texture *bg);
	void setGrid(Texture *gr);

	//Render
	void renderBg(Camera cam);
	void renderGrid(Camera cam);

private:
	Vector2 size;
	Texture *background;
	Texture *grid;
};

