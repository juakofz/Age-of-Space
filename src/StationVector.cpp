#include "StationVector.h"



StationVector::StationVector()
{
}



StationVector::~StationVector()
{
	//Clear vector if there is any element remaining
	if (!v_station.empty())
		v_station.clear();
}


bool StationVector::in(int i)
{
	if (!v_station.empty() && i <= v_station.size())
		return true;
	else
		return false;
}


void StationVector::add(Station * station)
{
	v_station.push_back(station);
}


void StationVector::erase(int i)
{
	if (in(i))
		v_station.erase(v_station.begin() + i); //Remove and destroy object
}

<<<<<<< HEAD
void StationVector::update()
{
	if (v_station.empty()) return;
	else
	{
		for (int i = 0; i < v_station.size(); i++)
		{
			v_station[i]->update();
		}
	}
}

void StationVector::update(GameObject * owner)
{
	if (v_station.empty()) return;
	else
	{
		for (int i = 0; i < v_station.size(); i++)
		{
			v_station[i]->update();
		}
	}
}
=======
>>>>>>> origin/rework

void StationVector::render(Camera cam)
{
	if (v_station.empty()) return;
	else
	{
		//...
	}
}


int StationVector::count()
{
	if (v_station.empty())
		return 0;
	else
		return v_station.size();
}
