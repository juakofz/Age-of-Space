#include "ListaExplosiones.h"



ListaExplosiones::ListaExplosiones()
{
}


ListaExplosiones::~ListaExplosiones()
{
	for (int i = 0;i<lista.size();i++)
	{
		delete lista[i];
		lista[i] = 0;
	}
}

bool ListaExplosiones::agregar(Explosion *exp)
{
	lista.push_back(exp);
	return true;
}

void ListaExplosiones::render(Camera cam)
{
	for (int i = 0;i<lista.size();i++)
	{
		if (!(lista[i]->render(cam))) eliminar(i);
	}
}

void ListaExplosiones::eliminar(int ind)
{
	if ((ind < 0) || (ind >= lista.size())) return;
	delete lista[ind];
	lista.erase(lista.begin() + ind);
}