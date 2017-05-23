#pragma once
#include "Vector2.h"
#include "Camera.h"
#include "Texture.h"
<<<<<<< HEAD
#include "GameObject.h"
=======
>>>>>>> origin/rework

class Ship;

class Station
{
public:
	Station();
	~Station();

	int getType();

	bool damage(float d);

	virtual bool update() = 0;
<<<<<<< HEAD
	void render(Camera cam);

protected:
=======
	virtual bool update(Ship * owner) = 0;
	void render(Camera cam);

private:
>>>>>>> origin/rework
	int m_type;
	Vector2 m_rel_pos; //From -1 to 1, relative to ship's center
	bool f_render;
	float m_max_health;
	float m_health;
	Texture * m_tex;
<<<<<<< HEAD
	GameObject * m_owner;
=======
>>>>>>> origin/rework

};

