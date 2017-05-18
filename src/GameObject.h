#pragma once

#include "Texture.h"
#include "Camera.h"
#include "Global.h"

class GameObject
{
public:

	GameObject(int type, int player);
	GameObject(int type); //For unselectable objects
	virtual ~GameObject();

	virtual int event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel) = 0;

	//Selection
	void select();
	void deselect();
	bool getSel();
	bool clickOn(SDL_Point pos);
	bool isInside(SDL_Rect rect);

	//Render
	virtual void render(Camera cam);
	void setMarker(Texture *m);

	//Position
	Vector2 getPos();
	virtual void setPos(float x, float y);
	virtual void setPos(Vector2 p);

	//Center
	Vector2 getCen();
	virtual void setCen(float x, float y);
	virtual void setCen(Vector2 c);

	//Size
	void scaleTo(int s);
	int getSize();
	Vector2 getDim();


	int getType();

	//Textures
	void setTex(Texture *t);
	static void setTextures(Texture *tdisp);

	//Player
	void setPlayer(int p);
	int getPlayer();

	//Health
	void setHealth(float h);
	float getHealth();
	bool damage(float d);

protected:

	const int m_type;

	Texture *m_marker, *m_tex;

	Vector2 m_pos;
	int m_width;
	int m_height;
	int m_size;
	Vector2 m_cen;

	float m_angle;
	bool f_sel = false;
	float m_sel_angle = 0;

	int m_player; //Owner
	bool m_selectable;

	float m_health;

};

