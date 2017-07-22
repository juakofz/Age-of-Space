#include "Quadtree.h"



Quadtree::Quadtree()
{
	//m_level = 0;
	//m_max_depth = 5;
	//m_max_objects = 8;
	//f_dead_end = true;
	//v_rects.emplace_back(m_quad);
	//clear();
}	


Quadtree::Quadtree(int level, SDL_Rect quad)
{
	m_level = level;
	m_quad = quad;
	m_max_depth = 5;
	m_max_objects = 15;
	f_dead_end = true;
	v_rects.emplace_back(m_quad);
	clear();
}


Quadtree::~Quadtree()
{
}


void Quadtree::clear()
{
	//Clear objects
	v_objects.clear();

	//Clear nodes
	for (int i = 0; i < 4; i++)
	{
		if (m_nodes[i] != NULL)
		{
			m_nodes[i]->clear();
			m_nodes[i] = NULL;
		}
	}

	f_dead_end = true;
}


void Quadtree::split()
{
	SDL_Rect new_quad;

	new_quad.w = m_quad.w / 2;
	new_quad.h = m_quad.h / 2;

	//Top left
	new_quad.x = m_quad.x;
	new_quad.y = m_quad.y;
	m_nodes[0] = new Quadtree(m_level + 1, new_quad);
	v_rects.emplace_back(new_quad);

	//Top Right
	new_quad.x = m_quad.x + new_quad.w;
	new_quad.y = m_quad.y;
	m_nodes[1] = new Quadtree(m_level + 1, new_quad);
	v_rects.emplace_back(new_quad);

	//Bottom Left
	new_quad.x = m_quad.x;
	new_quad.y = m_quad.y + new_quad.h;
	m_nodes[2] = new Quadtree(m_level + 1, new_quad);
	v_rects.emplace_back(new_quad);

	//Bottom Right
	new_quad.x = m_quad.x + new_quad.w;
	new_quad.y = m_quad.y + new_quad.h;
	m_nodes[3] = new Quadtree(m_level + 1, new_quad);
	v_rects.emplace_back(new_quad);
	
	f_dead_end = false;
}


void Quadtree::add(GameObject * obj)
{
	v_objects.add(obj);
}


bool * Quadtree::locate(GameObject * obj, bool * loc)
{
	Vector2 aux_cen = obj->getCen();
	int aux_rad = obj->getSize() / 2;

	SDL_Rect aux_quads[4];

	//Top left
	aux_quads[0].x = m_quad.x - aux_rad;
	aux_quads[0].y = m_quad.y - aux_rad;

	//Top right
	aux_quads[1].x = m_quad.x + m_quad.w / 2 - aux_rad;
	aux_quads[1].y = m_quad.y - aux_rad;

	//Bottom left
	aux_quads[2].x = m_quad.x - aux_rad;
	aux_quads[2].y = m_quad.y + m_quad.h / 2 - aux_rad;

	//Bottom right
	aux_quads[3].x = m_quad.x + m_quad.w / 2 - aux_rad;
	aux_quads[3].y = m_quad.y + m_quad.h / 2 - aux_rad;

	for (int i = 0; i < 4; i++)
	{
		loc[i] = false;

		aux_quads[i].w = m_quad.w / 2 + 2 * aux_rad;
		aux_quads[i].h = m_quad.h / 2 + 2 * aux_rad;

		if (aux_cen.x >= aux_quads[i].x && aux_cen.x <= aux_quads[i].x + aux_quads[i].w)
		{
			if (aux_cen.y >= aux_quads[i].y && aux_cen.y <= aux_quads[i].y + aux_quads[i].h)
			{
				loc[i] = true;
			}
		}
	}

	return loc;
}


int Quadtree::generate(ObjectVector * vector)
{
	//If invalid or empty object vector
	if (vector == NULL || vector->size() == 0)
		return 0;

	int total_quads = 1;
	v_objects = *vector;

	ObjectVector * aux_quad_objects[4];
	for (int n = 0; n < 4; n++)
	{
		aux_quad_objects[n] = new ObjectVector;
	}

	for (int i = 0; i < v_objects.size(); i ++)
	{
		//Locate every object
		GameObject * aux_object = v_objects.get(i);
		bool location[4];
		locate(aux_object, location);
		for (int j = 0; j < 4; j++)
		{
			//Store for corresponging quad
			if (location[j])
			{
				aux_quad_objects[j]->add(aux_object);
			}
		}
	}

	//If max depth has not been reached
	if (m_level < m_max_depth)
	{
		//Check if division is necessary
		for (int i = 0; i < 4; i++)
		{
			if (aux_quad_objects[i]->size() > m_max_objects)
			{
				//Split into subquads and iterate
				split();
				total_quads -= 1;

				for (int j = 0; j < 4; j++)
				{
					//Generate new quads from object subset and to count
					total_quads += m_nodes[j]->generate(aux_quad_objects[j]);
				}

				break;
			}
		}
	}

	return total_quads;
}


vector<ObjectVector> Quadtree::retrieve()
{

	vector<ObjectVector> big_vector;

	//If the quad is the end of a branch, add it's object vector
	if (f_dead_end)
	{
		big_vector.emplace_back(v_objects);
	}
	else
	{
		//Check every quad
		for (int i = 0; i < 4; i++)
		{
			//Iterate
			vector<ObjectVector> aux_vector = m_nodes[i]->retrieve();

			big_vector.insert(big_vector.end(), aux_vector.begin(), aux_vector.end());
		}
	}

	return big_vector;
}


void Quadtree::render_debug(Camera cam)
{
	if (!v_rects.empty())
	{
		SDL_Rect aux;
		aux.x = aux.y = 990;
		aux.w = aux.h = 20;

		v_rects.emplace_back(aux);
		for (int i = 0; i < v_rects.size(); i++)
		{
			SDL_Rect aux_rect = v_rects[i];

			aux_rect.x = aux_rect.x - cam.getPos().x;
			aux_rect.y = aux_rect.y - cam.getPos().y;

			SDL_SetRenderDrawColor(g_Renderer, 0, 255, 0, 0);
			SDL_RenderDrawRect(g_Renderer, &aux_rect);
		}
		v_rects.clear();
	}

	for (int i = 0; i < 4; i++)
	{
		if (m_nodes[i] != NULL)
			m_nodes[i]->render_debug(cam);
	}

}