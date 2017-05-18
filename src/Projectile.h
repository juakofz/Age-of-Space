#pragma once

#include "Global.h"
#include "MovingObject.h"
#include "Timer.h"

class Projectile :
	public MovingObject
{
public:
	Projectile(int type, int player, Vector2 origin, Vector2 dest);
	~Projectile(void);

	virtual bool move();

protected:
	float m_dmg;
	float m_speed;
	
	Timer t_life;
	float m_maxLifeTime;
	float m_lifeTime;
};
