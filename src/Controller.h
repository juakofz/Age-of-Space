#pragma once
#include "ListaNaves.h"
#include "ListaEdificios.h"

class Controller
{

public:
	Controller();
	~Controller();

	void setList(ListaNaves * l);
	bool agressive(int ind);

private:
	ListaNaves * naves;
	ListaEdificios * edificios;
};