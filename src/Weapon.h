#pragma once
#include "Station.h"
#include "Timer.h"
//#include "ObjectManager.h"

//class ObjectManager;

class Weapon : public Station
{
public:
	Weapon(int type, GameObject * owner);
	~Weapon();

	void setup();
	bool update();
	bool update(Ship * owner);

private:
	int m_projectile_type;
	float m_firerate;
	Timer t_fire;
};

