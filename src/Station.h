#pragma once
#include "Vector2.h"
#include "Camera.h"
#include "Texture.h"
#include "GameObject.h"


class Ship;

class Station
{
public:
	Station();
	~Station();

	int getType();

	bool damage(float d);

	virtual bool update() = 0;

	void render(Camera cam);

protected:

	int m_subtype;
	Vector2 m_rel_pos; //From -1 to 1, relative to ship's center
	bool f_render;
	float m_max_health;
	float m_health;
	Texture * m_tex;
	GameObject * m_owner;


};

