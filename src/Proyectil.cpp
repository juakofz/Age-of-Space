#include "Proyectil.h"


Proyectil::Proyectil(void):ObjetoMovil(false)
{

	//Vector2 por defecto 0,0;
	//Dirección predeterminada
	dir.x = 1;
	dir.y = 0;
	angle = 0;
	//Destino nulo
	dest.x = cen.x;
	dest.y = cen.y;
	//Velocidad máxima
	max_vel = 4;
	//Nave parada
	vel.x = 0;
	vel.y = 0;

	tex=NULL;
}


Proyectil::~Proyectil(void)
{
}
