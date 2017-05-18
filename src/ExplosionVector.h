#pragma once
#include <vector>
#include "Explosion.h"
#include "Camera.h"

class ExplosionVector
{
public:
	ExplosionVector();
	~ExplosionVector();

	bool in(int i);

	void add(Explosion * explosion);
	void erase(int i);

	void update();

	int count();

protected:
	vector<Explosion *> v_explosions;
};

