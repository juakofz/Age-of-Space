#pragma once
#include "Station.h"
#include "GameObject.h"
#include <vector>

class StationVector
{
public:
	StationVector();
	~StationVector();

	bool in(int i);

	void add(Station * station);
	void erase(int i);

	virtual void update();
	virtual void update(GameObject * owner);
	void render(Camera cam);

	int count();

private:
	vector<Station *> v_station;
};

