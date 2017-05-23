#pragma once
#include "Station.h"
<<<<<<< HEAD
#include "Timer.h"
//#include "ObjectManager.h"

//class ObjectManager;
=======


>>>>>>> origin/rework

class Weapon : public Station
{
public:
<<<<<<< HEAD
	Weapon(int type, GameObject * owner);
	~Weapon();

	void setup();
	bool update();
	bool update(Ship * owner);

private:
	int m_projectile_type;
	float m_firerate;
	Timer t_fire;
=======
	Weapon();
	~Weapon();

	bool update();
	bool update(Ship * owner);
>>>>>>> origin/rework
};

