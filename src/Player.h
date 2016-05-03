#pragma once

#include "Global.h"
#include <string.h>
#include <sstream>

class Player
{
	std::string name;
	unsigned int oro, energia;
	
public:

	Player(void);
	~Player(void);

	void setName(std::string nombre);
	std::string getName(void);

	void getRecursos(std::stringstream recursos[]);
};

