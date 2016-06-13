#include "Explosion.h"

Texture * Explosion::tex = 0;


Explosion::Explosion()
{
}



Explosion::Explosion(int x, int y, int size)
{
	//Posici�n
	pos.x = x;
	pos.y = y;

	//N�mero de proyectiles
	int p_num = size * scale;

	//Crear array de proyectiles
	Proyectil * proy = new Proyectil[p_num];
	for (int i = 0; i < p_num; i++)
	{
		//Textura
		proy[i].SetTex(tex);
		
		//Posici�n
		proy[i].SetPos(x, y);
		
		//�ngulo
		float angle = (360 / p_num) * i + (rand() % 11 - 5);
		
		//Direcci�n
		float dir_x = cos(M_PI * angle / 180);
		float dir_y = sin(M_PI * angle / 180);

		proy[i].SetDir(dir_x, dir_y);
		
		//Destino
		float reach = size * 10 * ((rand() % 100) / 50);
		float dest_x = pos.x + dir_x * reach;
		float dest_y = pos.y + dir_y * reach;
		
		proy[i].moveTo(dest_x, dest_y);

		//A�adir a lista
		l_proy.agregar(&proy[i]);
	}
}

bool Explosion::render(Camera cam)
{
	if (l_proy.getSize())
	{
		l_proy.render(cam);
		return 1;
	}
	else return 0;
}

void Explosion::setTexture(Texture * t)
{
	tex = t;
}