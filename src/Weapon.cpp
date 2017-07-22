#include "Weapon.h"


Weapon::Weapon(int type, GameObject * owner)
{
	v_requests = RequestList::getInstance();

	m_projectile_type = type;
	m_owner = owner;
	setup();
	t_fire.start();
}

Weapon::~Weapon()
{
}

void Weapon::setup()
{
	switch (m_projectile_type)
	{
	case WEAPON_LASER:
		m_firerate = 1.0f; //2 shots/sec
		break;
	case WEAPON_MINILASER:
		m_firerate = 5.0f; //5 shots/sec
		break;
	}
}

bool Weapon::update()
{
	if (t_fire.getTicks() < (1000.0f / m_firerate))
		return false;
	else
	{
		//cout << "Bang!" << endl;
		Request proj = { m_projectile_type, m_owner->getPlayer(),
						 m_owner->getCen(), m_owner->getObjective() };
		v_requests->addRequest(proj);
		t_fire.restart();
		return true;
	}
}