#include "Proyectil.h"



Proyectil::Proyectil(int p):ObjetoMovil(3, false)
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
	max_vel = 6;

	//Nave parada
	vel.x = 0;
	vel.y = 0;

	tex = NULL;

	player = p;
}

Proyectil::~Proyectil(void)
{
}

bool Proyectil::move()
{
	if ((abs(cen.x - dest.x) > max_vel) || (abs(cen.y - dest.y) > max_vel)) {

		//Ajuste de velocidades
		vel.x = max_vel * cos(M_PI * angle / 180);
		vel.y = max_vel * sin(M_PI * angle / 180);
		
		//Movimiento
		SetCen(cen.x + vel.x, cen.y + vel.y);
	}
	else
	{
		return 1;
	}
	return 0;
}