#pragma once

#include "MovingObject.h"
#include "Timer.h"

class Projectile :
	public MovingObject
{
public:
	Projectile(int p = 0);
	~Projectile(void);

	virtual bool move();

protected:
	float m_dmg;
	float m_speed;
	
	Timer t_life;
	float m_maxLifeTime;
	float m_lifeTime;
};
