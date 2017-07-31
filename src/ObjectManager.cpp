#include "ObjectManager.h"


ObjectManager * ObjectManager::s_instance = 0;

ObjectManager::ObjectManager()
{
	v_requests = RequestList::getInstance();

	v_explosions = new T_Vector<Explosion>;
	v_objects = new ObjectVector;
	
	SDL_Rect map{ 0, 0, g_MAP_WIDTH, g_MAP_HEIGHT };

	qt_interactions = * new Quadtree(0, map);
}



ObjectManager::~ObjectManager()
{
}

//--------------------------------------------------------------------------------------//

//General

void ObjectManager::handleRequests()
{
	while (v_requests->check()) 
	{
		m_request = v_requests->popRequest(); //Extract request
		
		switch (m_request.type) //Create objects
		{
		case WEAPON_LASER:
			createProjectile(m_request.type, m_request.player, m_request.center, m_request.dest);
			break;

		case WEAPON_MINILASER:
			createProjectile(m_request.type, m_request.player, m_request.center, m_request.dest);
			break;

		default:
			break;
		}
	} 
}


void ObjectManager::update()
{
	kill(); //Delete dead entities

	if (v_objects->check()) //Regenerate quadtree
	{
		qt_interactions.generate(v_objects);
		vv_quadvectors.clear();
		vv_quadvectors = qt_interactions.retrieve();
	}
}

void ObjectManager::deleteOne()
{
	if (v_objects->check())
	{
		for (int i = 0; i < v_objects->size(); i++)
		{
			//If object is selected
			if (v_objects->get(i)->getSel())
			{
				//If object is alive
				if (v_objects->get(i)->isAlive())
				{
					v_objects->get(i)->kill();

					if (!(g_keyboardState[SDL_SCANCODE_LSHIFT] || g_keyboardState[SDL_SCANCODE_RSHIFT]))
					{
						return;
					}
				}
			}
		}
	}
}

void ObjectManager::kill()
{
	if (v_objects->check())
	{
		for (int i = 0; i < v_objects->size(); i++)
		{
			if (!v_objects->get(i)->isAlive())
			{
				if (v_objects->get(i)->getType() == TYPE_SHIP)
				{
					createExplosion(v_objects->get(i)->getCen().x, v_objects->get(i)->getCen().y, v_objects->get(i)->getSize());
				}
				v_objects->erase(i);
				i--;
			}
		}
	}
}

//--------------------------------------------------------------------------------------//

//Projectiles
void ObjectManager::createProjectile(int type, int player, Vector2 origin, Vector2 dest)
{
	Projectile * aux_proj = new Projectile(type, player, origin, dest);
	v_objects->add(aux_proj);
}

//--------------------------------------------------------------------------------------//

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
	//v_explosions->update();
}

//--------------------------------------------------------------------------------------//

//Ships
void ObjectManager::createShip(int type, int player, Vector2 center)
{
	Ship * aux_ship = new Ship(type, player, center);
	v_objects->add(aux_ship);
}


void ObjectManager::shipEvents(SDL_Event * e, SDL_Rect sel, SDL_Point xy_rel)
{
	v_objects->event(e, sel, xy_rel);
}


void ObjectManager::move()
{
	v_objects->update();
	shipOverlap();
	kill();	
	v_objects->move();
}


void ObjectManager::render(Camera cam)
{
	v_objects->render(cam);
	if(g_f_debug)
		qt_interactions.render_debug(cam);
}

//--------------------------------------------------------------------------------------//

//Interactions -- move to interactions class
bool ObjectManager::collision(Vector2 cen1, float size1, Vector2 cen2, float size2)
{
	float aux_dist = cen1.distance(cen2);
	if (aux_dist < size1 || aux_dist < size2)
		return true;
	else
		return false;
}

bool ObjectManager::collision(GameObject * obj1, GameObject *obj2)
{
	Vector2 cen1 = obj1->getCen();
	Vector2 cen2 = obj2->getCen();

	float size1 = obj1->getSize();
	float size2 = obj2->getSize();

	float aux_dist = cen1.distance(cen2);
	if (aux_dist < size1 || aux_dist < size2)
		return true;
	else
		return false;

}


void ObjectManager::projectileImpacts()
{
	if (vv_quadvectors.empty()) return;

	//For every object vector
	for (int n_vec = 0; n_vec < vv_quadvectors.size(); n_vec++)
	{
		//If it's not empty
		if (vv_quadvectors[n_vec].check())
		{
			//For every element
			for (int n_proj = 0; n_proj < vv_quadvectors[n_vec].size(); n_proj++) 
			{
				//if alive projectile
				if (vv_quadvectors[n_vec].get(n_proj)->getType() == TYPE_PROJECTILE && vv_quadvectors[n_vec].get(n_proj)->isAlive())
				{
					//For every other element
					for (int n_ship = 0; n_ship < vv_quadvectors[n_vec].size(); n_ship++)
					{
						//if alive ship
						if (vv_quadvectors[n_vec].get(n_ship)->getType() == TYPE_SHIP&& vv_quadvectors[n_vec].get(n_ship)->isAlive())
						{
							//If ennemies
							if (vv_quadvectors[n_vec].get(n_proj)->getPlayer() != vv_quadvectors[n_vec].get(n_ship)->getPlayer())
							{ 
								//IF collision happens
								if (collision(vv_quadvectors[n_vec].get(n_proj), vv_quadvectors[n_vec].get(n_ship)))
								{
									//Damage ship
									float aux_dmg = Interactions::calculateDamage(vv_quadvectors[n_vec].get(n_ship), vv_quadvectors[n_vec].get(n_proj));
									if (vv_quadvectors[n_vec].get(n_ship)->damage(aux_dmg)) //If ship was destroyed
									{
										//Create explosion										
										//createExplosion(vv_quadvectors[n_vec].get(n_ship)->getCen().x, vv_quadvectors[n_vec].get(n_ship)->getCen().y, 10);
										vv_quadvectors[n_vec].get(n_ship)->kill();//Set as dead
									}

									vv_quadvectors[n_vec].get(n_proj)->kill(); //Set as dead

								}
							}
						}
					}
				}
			}
		}
	}
}

//Can be combined with the other check loop
void ObjectManager::shipOverlap()
{
	if (vv_quadvectors.empty()) return;
	
	//For every vector
	for (int v = 0; v < vv_quadvectors.size(); v++)
	{
		//If not empty
		if (vv_quadvectors[v].check())
		{
			//For every element
			for (int i = 0; i < vv_quadvectors[v].size(); i++)
			{
				//For every other element
				for (int j = i + 1; j < vv_quadvectors[v].size(); j++)
				{
					//Collision
					if (collision(vv_quadvectors[v].getCen(i), vv_quadvectors[v].getSize(i),
						vv_quadvectors[v].getCen(j), vv_quadvectors[v].getSize(j)))
					{
						//Collide
						shipRepel(vv_quadvectors[v].get(i), vv_quadvectors[v].get(j));
					}			
				}
			}
		}
	}
}


void ObjectManager::shipRepel(GameObject * s1, GameObject * s2)
{
	if (s1->getType() == TYPE_SHIP && s2->getType() == TYPE_SHIP)
	{
		Vector2 aux_repulsion = s1->getCen() - s2->getCen();
		if (aux_repulsion.length() < 0.001) //For perfect overlapping, repulsion might be 0
			aux_repulsion = (0, 1); 
		float repel_force = 0.05f;

		s1->addVel(aux_repulsion.normalize(repel_force)); //Repel ship i
		s2->addVel(-aux_repulsion.normalize(repel_force)); //Repel ship j in opposite direction
	}
}

//--------------------------------------------------------------------------------------//

//Minimap
void ObjectManager::renderMinimap()
{
	//if (v_objects->check())
	//{
	//	//for (int i = (v_objects->getSize() - 1); i >= 0; i--)
	//	for (int i = 0; i < v_objects->getSize(); i ++)
	//	{
	//		if (v_objects->getType() == TYPE_SHIP)
	//		{

	//		}


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