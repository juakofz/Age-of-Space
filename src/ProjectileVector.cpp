#include "ProjectileVector.h"



ProjectileVector::ProjectileVector()
{
}


ProjectileVector::~ProjectileVector()
{
	//Clear vector if there is any element remaining
	if (!v_projectile.empty())
		v_projectile.clear();
}

bool ProjectileVector::in(int i)
{
	if (!v_projectile.empty() && i <= v_projectile.size())
		return true;
	else
		return false;
}

void ProjectileVector::add(Projectile * projectile)
{
	v_projectile.push_back(projectile);
}

void ProjectileVector::erase(int i)
{
	if (in(i))
		v_projectile.erase(v_projectile.begin() + i); //Remove and destroy object
}

int ProjectileVector::count()
{
	if (v_projectile.empty())
		return 0;
	else
		return v_projectile.size();
}

Projectile * ProjectileVector::get(int i)
{
	if (in(i))
	{
		Projectile * aux_proj = v_projectile[i];
		return aux_proj;
	}
	else
		return NULL;
}

Vector2 ProjectileVector::getCen(int i)
{
	Vector2 aux;
	if (!in(i))
		return aux; //Zero
	else
	{
		aux = v_projectile[i]->getCen();
		return aux;
	}
}

float ProjectileVector::getSize(int i)
{
	if (!in(i))
		return 0;
	else
		return v_projectile[i]->getSize();
}

void ProjectileVector::move()
{
	if (v_projectile.empty()) return;
	else
	{
		for (int i = 0; i < v_projectile.size(); i++)
		{
			//If projectile reached it's destination or died
			if (v_projectile[i]->move()) 
			{
				erase(i); //Delete projectile

				//Update iterator
				if (i > 0)
					i--;
				else
					break;
			}
		}
	}
}

void ProjectileVector::render(Camera cam)
{
	if (v_projectile.empty()) return;
	else
	{
		for (int i = 0; i < v_projectile.size(); i++)
		{
			v_projectile[i]->render(cam);
		}
	}
}

