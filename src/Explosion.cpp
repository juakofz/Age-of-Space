#include "Explosion.h"

Texture * Explosion::tex = 0;
float Explosion::scale=0.6;

Explosion::Explosion()
{
}

Explosion::~Explosion()
{
	cout << "no pum" << endl;
}

Explosion::Explosion(int x, int y, int size)
{
	cout << "pum" << endl;
	//Posición
	pos.x = x;
	pos.y = y;

	//Número de proyectiles
	int p_num = size * scale;

	//Crear array de proyectiles
	Proyectil * proy = new Proyectil[p_num];
	for (int i = 0; i < p_num; i++)
	{
		//Textura
		proy[i].SetTex(tex);
		proy[i].setSize(25);
		tex->setColor(230 + (rand() % 35), 110 + (rand() % 40), (rand () % 30));

		//Posición
		proy[i].SetPos(x, y);
		proy[i].SetMaxVel(2);

		//Ángulo
		float angle = (360 / p_num) * i + (rand() % 11 - 5);
		
		//Dirección
		float dir_x = cos(M_PI * angle / 180);
		float dir_y = sin(M_PI * angle / 180);

		proy[i].SetDir(dir_x, dir_y);
		
		//Destino
		float reach = size * 0.05 * ((rand() % 100) / 5);
		float dest_x = pos.x + dir_x * reach;
		float dest_y = pos.y + dir_y * reach;
		
		proy[i].moveTo(dest_x, dest_y);

		//Añadir a lista
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