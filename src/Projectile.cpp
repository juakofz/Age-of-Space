#include "Projectile.h"



Projectile::Projectile(int p):MovingObject(3, false) //Non selectable
{
	m_dir.x = 1;
	m_dir.y = 0;
	m_angle = 0;

	m_dest = m_cen; //No destination
	m_vel.makeZero(); //Stopped
	m_tex = NULL; //No texture
	m_player = p; //Owner

	m_speed = 1.0f;

	m_maxLifeTime = 2.0f; //2 secs
	m_lifeTime = 0.0f;
	t_life.start(); //Start life timer
}

Projectile::~Projectile(void)
{
}

bool Projectile::move()
{
	//if (t_life.getSecs() >= m_maxLifeTime) //If lifetime has expired
	//	return true;
	//else
	if (m_cen.distance(m_dest) < m_vel.length()) //If target has been reached
		return true;
	else
	{
		setCen(m_cen + m_vel);
		return false;
	}
	
}