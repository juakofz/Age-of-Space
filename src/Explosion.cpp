#include "Explosion.h"


Explosion::Explosion(int x, int y, int size)
{
	m_cen.x = x; //Explosion center
	m_cen.y = y;
	m_number = size * m_scale; //Projectile number

	//Create projectiles via object manager
	for (int i = 0; i < m_number; i++)
	{
		float interval = 360 / m_number;
		float angle = interval * i + g_rand_float(-interval/2, interval/2); //Slightly random angle
		float reach = size * 0.5 * ((rand() % 100) / 5 + 1); //Destination
		Vector2 dest = m_cen + Vector2::toVector(angle, reach);
		v_directions.push_back(dest);
	}
}

Explosion::Explosion(Vector2 cen, int size)
{
	m_cen = cen; //Explosion center
	m_number = size * m_scale; //Projectile number

	//Create projectiles via object manager
	for (int i = 0; i < m_number; i++)
	{
		float angle = (360 / m_number) * i + (rand() % 11 - 5); //Slightly random angle
		float reach = size * 0.05 * ((rand() % 100) / 5); //Destination
		Vector2 dest = m_cen + Vector2::toVector(angle, reach);
		v_directions.push_back(dest);
	}

}

Explosion::~Explosion()
{
	v_directions.clear();
}
