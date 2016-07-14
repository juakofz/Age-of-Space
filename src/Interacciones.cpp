#include "Interacciones.h"


Interacciones::Interacciones(void)
{
}


Interacciones::~Interacciones(void)
{
}

bool Interacciones::impacto(Ship nave, Proyectil disparo)
{
	if ((nave.GetCen() - disparo.GetCen()).modulo() < ((disparo.getSize() / 2 + nave.getSize() / 2 ) / 2))
		{
			return 1;
	}
	return 0;
	//nave.getSize() / 4 + disparo.getSize() / 4
}


int Interacciones::impactoListas(ListaNaves &n, ListaProyectiles &p)
{
	int flag = 0;

	for (int i = (n.lista.size() - 1); i >= 0; i--)
	{
		for (int j = (p.lista.size() - 1); j >= 0; j--)
		{
			if(impacto(*n.lista[i], *p.lista[j]) && (n.lista[i]->getPlayer() != p.lista[j]->getPlayer()))
			{
				n.eliminarNave(i);
				p.eliminarProyectil(j);
				//cout << "impacto" << endl;

				flag++;
				break;				
			}
		}
	}
	return flag;
}

bool Interacciones::impacto(Edificio &edif, ListaProyectiles &d)
{
	for(int i = 0; i<d.lista.size(); i++)
	{
		if(impacto(edif, *d.lista[i]))
		{
			d.eliminarProyectil(i);
			//cout<<"impacto"<<endl;
			if(edif.golpeada()) return 1;
			else return 0;
		}
	}
	return false;
}

bool Interacciones::impacto(Edificio edif, Proyectil disparo)
{
	if ((edif.GetCen() - disparo.GetCen()).modulo() < ((disparo.getSize() / 2 + edif.getSize() / 2 ) / 2))
	{
			return 1;
	}
	return 0;
}