#include "Weapon.h"


Weapon::Weapon(Ship * owner, Vector2 rel_pos)
{
	m_owner = owner;
	m_rel_pos = rel_pos;
	init();
}

Weapon::~Weapon()
{
}

void Weapon::init()
{
	//Combat values
	m_dmg = 1.0f;
	m_speed = 4.0f;
	m_fireRate = 1.0f; // 1 shootings/sec

	update();

}

void Weapon::setRelPos(Vector2 rel_pos)
{
	if (rel_pos.x > 1)
		rel_pos /= rel_pos.x;

	if (rel_pos.y > 1)
		rel_pos /= rel_pos.y;

	m_rel_pos = rel_pos;
}

void Weapon::shoot(Vector2 target_pos)
{
	//Fire timer
	if (!t_fire.isStarted())
	{
		//Do the shootings
		t_fire.start();
	}
	else if (t_fire.getSecs() > (1 / m_fireRate))
	{
		//Do the shootings
		t_fire.restart();
	}
	else
	{
		//Do not do the shootings
	}
}

void Weapon::update()
{
	//Update position
	Vector2 aux_pos;

	aux_pos.x = m_rel_pos.x * m_owner->getDim().x; //Relative position
	aux_pos.y = m_rel_pos.y * m_owner->getDim().y;

	float aux_angle = m_owner->getAngle();
	aux_pos.rotateTo(aux_angle); //Rotate as owner
	aux_pos += m_owner->getCen(); //Add owner's center position
	
	m_cen = aux_pos;
}