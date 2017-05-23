#pragma once
#include "Station.h"
<<<<<<< HEAD
#include "GameObject.h"
#include <vector>

=======
#include <vector>



>>>>>>> origin/rework
class StationVector
{
public:
	StationVector();
	~StationVector();

	bool in(int i);

	void add(Station * station);
	void erase(int i);

<<<<<<< HEAD
	virtual void update();
	virtual void update(GameObject * owner);
=======
>>>>>>> origin/rework
	void render(Camera cam);

	int count();

private:
	vector<Station *> v_station;
};

