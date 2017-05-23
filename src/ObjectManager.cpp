#include "ObjectManager.h"


ObjectManager * ObjectManager::s_instance = 0;

ObjectManager::ObjectManager()
{
	v_ships = new ShipVector;
	v_projectiles = new ProjectileVector;
	v_explosions = new ExplosionVector;
}

ObjectManager::ObjectManager(ShipVector * ships, ProjectileVector * projectiles,
								ExplosionVector * explosions)
{
	v_projectiles = projectiles;
	v_explosions = explosions;
	v_ships = ships;
}


ObjectManager::~ObjectManager()
{
}


//Projectiles
void ObjectManager::createProjectile(int type, int player, Vector2 origin, Vector2 dest)
{
	Projectile * aux_proj = new Projectile(type, player, origin, dest);
	v_projectiles->add(aux_proj);
}


void ObjectManager::moveProjectiles()
{
	v_projectiles->move();
}


void ObjectManager::renderProjectiles(Camera cam)
{
	v_projectiles->render(cam);
}


//Explosions
void ObjectManager::createExplosion(int x, int y, int size)
{
	Vector2 cen(x, y);
	Explosion * aux_expl = new Explosion(x, y, size);
	if (!aux_expl->v_directions.empty())
	{
		for (int i = 0; i < aux_expl->v_directions.size(); i++)
		{
			createProjectile(0, 0, cen, aux_expl->v_directions[i]);
		}
	}
	v_explosions->add(aux_expl);
}

void ObjectManager::updateExplosions()
{
	v_explosions->update();
}


//Ships
void ObjectManager::createShip(int type, int player, Vector2 center)
{
	Ship * aux_ship = new Ship(type, player, center);
	v_ships->add(aux_ship);
}

void ObjectManager::shipEvents(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel)
{
	v_ships->event(e, sel, xy_rel);
}


void ObjectManager::moveShips()
{
	v_ships->move();
	shipOverlap();
	v_ships->update();
}


void ObjectManager::renderShips(Camera cam)
{
	v_ships->render(cam);
}


//Interactions
bool ObjectManager::collision(Vector2 cen1, float size1, Vector2 cen2, float size2)
{
	float aux_dist = cen1.distance(cen2);
	if (aux_dist < (size1 + size2) / 2)
		return true;
	else
		return false;
}

void ObjectManager::projectileImpacts()
{
	if (v_projectiles->count() > 0 && v_ships->count() > 0)
	{
		for (int i = 0; i < v_projectiles->count(); i++) //For every projectile
		{
			for (int j = 0; j < v_ships->count(); j++) //Check every ship
			{
				bool f_impact = collision(v_projectiles->getCen(i), v_projectiles->getSize(i),
					v_ships->getCen(j), v_ships->getSize(j));
				if (f_impact)
				{					

					//Damage ship
					float aux_dmg = Interactions::calculateDamage(v_ships->get(j), v_projectiles->get(i));
					if (v_ships->damage(j, aux_dmg)) //If ship was destroyed
					{
						createExplosion(v_ships->getCen(j).x, v_ships->getCen(j).y, 10);
						v_ships->erase(j);
						j--;
					}

					v_projectiles->erase(i); //Delete projectile
					i--;
				}
			}
		}
	}
}

void ObjectManager::shipOverlap()
{
	if (v_ships->count() > 0)
	{
		for (int i = 0; i < v_ships->count(); i++)
		{
			for (int j = i + 1; j < v_ships->count(); j++)
			{
					if (collision(v_ships->getCen(i), v_ships->getSize(i),
								  v_ships->getCen(j), v_ships->getSize(j)))
						v_ships->repel(i, j);
			}
		}
	}
}

//Minimap
void ObjectManager::renderMinimap()
{
	//if (naves.getSize()) {
	//	for (int i = (naves.getSize() - 1); i >= 0; i--)
	//	{
	//		Vector2 p = naves.getCen(i);
	//		Vector2 rp;
	//		rp.x = (p.x / map.getSize().x) * (w - 2 * margen) + margen;
	//		rp.y = (p.y / map.getSize().y) * (h - 2 * margen) + margen;

	//		SDL_Rect fillRect = {rp.x, rp.y, 2, 2};
	//		switch (naves.getPlayer(i))
	//		{
	//		case 1:
	//			SDL_SetRenderDrawColor(g_Renderer, 0, 255, 255, 0);
	//			break;
	//		case 2:
	//			SDL_SetRenderDrawColor(g_Renderer, 255, 0, 0, 0);
	//			break;
	//		default:
	//			SDL_SetRenderDrawColor(g_Renderer, 0, 0, 0, 0);
	//		}
	//		SDL_RenderFillRect(g_Renderer, &fillRect);
	//	}
	//}
}