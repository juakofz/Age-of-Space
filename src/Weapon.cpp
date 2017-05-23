#include "Weapon.h"



<<<<<<< HEAD
Weapon::Weapon(int type, GameObject * owner)
{
	m_projectile_type = type;
	m_owner = owner;
	setup();
	t_fire.start();
=======
Weapon::Weapon()
{
>>>>>>> origin/rework
}


Weapon::~Weapon()
{
}

<<<<<<< HEAD
void Weapon::setup()
{
	switch (m_projectile_type)
	{
	case WEAPON_LASER:
		m_firerate = 2.0f; //2 shots/sec
		break;
	case WEAPON_MINILASER:
		m_firerate = 5.0f;
		break;
	}
}

bool Weapon::update()
{
	if (t_fire.getSecs() < 1 / m_firerate)
		return false;
	else
	{
		cout << "Bang!" << endl;
		t_fire.restart();
		return true;
		//ObjectManager * aux_manager = ObjectManager::getInstance();
	}
=======

bool Weapon::update()
{
	return false;
}

bool Weapon::update(Ship * owner)
{
	//Non predictive shooting
	return false;
>>>>>>> origin/rework
}