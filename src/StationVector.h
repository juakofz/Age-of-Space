#pragma once
#include "Station.h"
#include <vector>



class StationVector
{
public:
	StationVector();
	~StationVector();

	bool in(int i);

	void add(Station * station);
	void erase(int i);

	void render(Camera cam);

	int count();

private:
	vector<Station *> v_station;
};

