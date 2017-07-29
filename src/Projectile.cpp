#include "Projectile.h"


Projectile::Projectile(int subtype, int player, Vector2 origin, Vector2 dest):MovingObject(TYPE_PROJECTILE, subtype, player) //Non selectable
{

	switch (subtype)
	{
	case WEAPON_MINILASER:

		setTex(&g_tex[10]); //Red laser texture

		m_player = player; //Owner
		scaleTo(8);
		m_speed = 6.0f; //Constant speed
		m_dmg = 0.5f; //Damage
		m_maxLifeTime = 2.0f; //2 secs life
		m_lifeTime = 0.0f;
		t_life.start(); //Start life timer
		
		break;

	case WEAPON_LASER:

		setTex(&g_tex[9]); //Blue laser texture

		m_player = player; //Owner
		scaleTo(15);
		m_speed = 4.0f; //Constant speed
		m_dmg = 2.5f; //Damage
		m_maxLifeTime = 4.0f; //2 secs life
		m_lifeTime = 0.0f;
		t_life.start(); //Start life timer

		break;

	//Default: explosion projectile
	default:

		setTex(&g_tex[10]); //Red laser texture

		m_player = player; //Owner
		scaleTo(10);
		m_speed = 3.0f; //Constant speed
		m_dmg = 0.2f; //Damage
		m_maxLifeTime = 2.0f; //2 secs life
		m_lifeTime = 0.0f;
		t_life.start(); //Start life timer

		break;
	}

	setCen(origin); //Origin
	setDest(dest); //Destination
	setDir(dest - origin); //Direction and angle
	setVel(m_dir.normalize(m_speed)); //Velocity
}

Projectile::~Projectile(void)
{
}

float Projectile::getDmg()
{
	return m_dmg;
}

bool Projectile::move()
{
	if (t_life.getSecs() >= m_maxLifeTime) //If lifetime has expired
		return true;
	else if (m_cen.distance(m_dest) < m_vel.length()) //If target has been reached
		return true;
	else
		setCen(m_cen + m_vel);

	return false;
}