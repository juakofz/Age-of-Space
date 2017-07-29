#pragma once

#include "Texture.h"
#include "Camera.h"
#include "Global.h"


class GameObject
{
public:

	GameObject(int type, int subtype, int player);
	virtual ~GameObject();

	virtual int event(SDL_Event* e, SDL_Rect selection, SDL_Point xyrel);

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

	//Objective
	Vector2 getObjective();
	virtual void setObjective(float x, float y);
	virtual void setObjective(Vector2 c);

	//Movement
	virtual bool move();
	virtual void update();
	virtual void addVel(Vector2 v);

	//Size
	void scaleTo(int s);
	int getSize();
	Vector2 getDim();

	//Type
	int getType();
	int getSubType();

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
	bool isAlive();
	void kill();

protected:

	const int m_type;	//Object type: ship, projectile...
	const int m_subtype;		//Object subtype: figter, missile, transport...

	Texture *m_marker, *m_tex;

	Vector2 m_pos;
	int m_width;
	int m_height;
	int m_size;
	Vector2 m_cen;
	Vector2 m_objective;

	float m_angle;
	bool f_sel = false;
	float m_sel_angle = 0;

	int m_player; //Owner
	bool m_selectable;

	//Health
	bool f_alive;
	float m_max_health;
	float m_health;

	//Shields
	float m_max_shields;
	float m_shields;

	//Armor
	float m_armor;
};

