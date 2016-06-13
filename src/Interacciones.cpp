#include "Interacciones.h"


Interacciones::Interacciones(void)
{
}


Interacciones::~Interacciones(void)
{
}

bool Interacciones::impacto(Ship nave, Proyectil disparo)
{
	if ((nave.GetCen()-disparo.GetCen()).modulo() < 1) return 1;
	return 0;
}

bool Interacciones::impactoListas(ListaNaves &n, ListaProyectiles &p)
{
	for (int i=0;i<n.lista.size();i++)
	{
		for (int j=0;j<p.lista.size();j++)
			{
				if(impacto(*n.lista[i], *p.lista[j]))
				{

					n.eliminarNave(i);
					p.eliminarProyectil(j);
				}
		}
	}
	return 1;
}
