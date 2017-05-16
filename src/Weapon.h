#pragma once
#include "MovingObjectVector.h"
#include "Ship.h"

//typedef enum {LASER}e_weapon_type; idea

class Weapon
{
public:
	Weapon(Ship * owner, Vector2 rel_pos);
	~Weapon();

	void init();
	void setRelPos(Vector2 rel_pos);
	void shoot(Vector2 target_pos);
	void update();

private:
	
	Ship * m_owner; //Pointer to owner
	Vector2 m_rel_pos; //Weapon position relative to owner's center
	Vector2 m_cen; //Map coordinates

	float m_dmg; //Weapon damage per projectile
	float m_speed; //Projectile speed

	float m_fireRate; //Weapon firerate in Hz
	Timer t_fire; //Firerate timer

	MovingObjectVector v_projectiles; //Projectiles vector
};

