//not in use

#pragma once
#include "ListaNaves.h"
#include "ListaEdificios.h"

class Controller
{

public:
	Controller();
	~Controller();

	void setList(ListaNaves * l);
	void setList(ListaEdificios * l);
	void setList(Edificio * e);
	bool agressive(int ind);

private:
	ListaNaves * naves;
	ListaEdificios * edificios;
	Edificio * edificio;
};