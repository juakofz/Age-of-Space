#include "Projectile.h"


Projectile::Projectile(int type, int player, Vector2 origin, Vector2 dest):MovingObject(3, false) //Non selectable
{
	//Type 0: explosion projectile
	if (type == 0)
	{
		Texture * aux_tex = &g_tex[10]; //Red laser texture
		setTex(aux_tex);

		m_player = player; //Owner
		scaleTo(10);
		m_speed = 3.0f; //Constant speed
		m_maxLifeTime = 2.0f; //2 secs life
		m_lifeTime = 0.0f;
		t_life.start(); //Start life timer
		
	}

	//Type 1: small laser
	if (type == 1)
	{
		Texture * aux_tex = &g_tex[9]; //Blue laser texture
		setTex(aux_tex);

		m_player = player; //Owner
		scaleTo(12);
		m_speed = 5.0f; //Constant speed
		m_maxLifeTime = 2.0f; //2 secs life
		m_lifeTime = 0.0f;
		t_life.start(); //Start life timer
	}

	setCen(origin); //Origin
	setDest(dest); //Destination
	setDir(dest - origin); //Direction and angle
	setVel(m_dir.normalize(m_speed)); //Velocity
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
		setCen(m_cen + m_vel);

	return false;
}