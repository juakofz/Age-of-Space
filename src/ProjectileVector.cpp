#include "ProjectileVector.h"



Vector2 ProjectileVector::getCen(int i)
{
	Vector2 aux;
	if (!in(i))
		return aux; //Zero
	else
	{
		aux = v_elements[i]->getCen();
		return aux;
	}
}

float ProjectileVector::getSize(int i)
{
	if (!in(i))
		return 0;
	else
		return v_elements[i]->getSize();
}

int ProjectileVector::getPlayer(int i)
{
	if (!in(i))
		return 0;
	else
		return v_elements[i]->getPlayer();
}


void ProjectileVector::move()
{
	if (v_elements.empty()) return;
	else
	{
		for (int i = 0; i < v_elements.size(); i++)
		{
			//If projectile reached it's destination or died
			if (v_elements[i]->move()) 
			{
				erase(i); //Delete projectile

				//Update iterator
				if (i > 0)
					i--;
			}
		}
	}
}

void ProjectileVector::render(Camera cam)
{
	if (v_elements.empty()) return;
	else
	{
		for (int i = 0; i < v_elements.size(); i++)
		{
			v_elements[i]->render(cam);
		}
	}
}

