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