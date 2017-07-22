#pragma once
#include "Station.h"
#include "Timer.h"
#include "RequestList.h"

class GameObject;


class Weapon : public Station
{
public:
	Weapon(int type, GameObject * owner);
	~Weapon();

	void setup();
	bool update();
	bool update(GameObject * owner);

private:
	int m_projectile_type;
	float m_firerate;
	Timer t_fire;
	GameObject * m_owner;
	RequestList * v_requests;
};

