//not in use

#include "Controller.h"


Controller::Controller()
{
	naves = 0;
}


Controller::~Controller()
{
}

void Controller::setList(ListaNaves * l)
{
	if(l) naves = l;
}

void Controller::setList(ListaEdificios * l)
{
	if (l) edificios = l;
}

void Controller::setList(Edificio * e)
{
	if (e) edificio = e;
}

bool Controller::agressive(int ind)
{
	if (!naves) return false;

	int r_time = 1000; //Order time
	bool s_flag = false; //Shoot flag
	bool t_flag = false; //Target flag

	Ship * self = naves->getShip(ind);
	if (!self) return false;

	//std::cout<<unit->getState()<<endl;

	 self->move();
	/*//State machine: 0 = standby, 1 = moving, 2 = attacking 
	switch (self->getState())
	{

	case 0: //Stand by
	{
		//Order time = 1 s
		if (self->getTimer()->isStarted() && (self->getTimer()->getTicks() <= r_time))
		{
			return false;
		}
		else
		{
			//Targetting
			for (int i = (naves->getSize() - 1); i >= 0; i--)
			{
				Ship * nave = naves->getShip(i);

				if (naves->getPlayer(i) != self->getPlayer()) //Different players
				{
					if (self->inSight(nave)) //Within sight
					{
						self->setTarget(naves->getShip(i)); //Target acquired
						t_flag = true;
						break;
					}
				}
			}

			//Attack main building
			if (!t_flag && (self->getPlayer() == 2))
			{
				self->setTarget(edificio); //Target acquired
				t_flag = true;
			}

			//Movement
			if (!(self->onTarget())) //Not on target
			{
				self->turn(self->getDest()); //Turn
			}

			else //On target
			{
				if (self->inRange()) //Within range
				{
					s_flag = self->attack(); //Check attack timer
				}
				else //Move towards target
				{
					self->move();
				}
			}
			self->getTimer()->restart(); //Order timer
			self->setState(2); //Switch to attacking

			return s_flag;
		}
		return false;
		break;
	}

	case 1: //Moving (direct order)
	{
		//Reached destination
		if (self->onDest())
		{
			self->setState(0); //Standby
		}
		else
		{
			//si es orden directa no tienes target!
			//if (unit->onTarget()) //Oriented towards dest

			//{
			//	unit->move(); //Straight
			//}
			//else //Not oriented
			{
				if(self->turn()) self->setState(0);
			}
		}
		return false; //No shooting
		break;
	}

	case 2: //Attacking
	{
		//cout<<"atacando"<<endl;
		//Order timer
	//	if (unit->getTimer()->isStarted() && (unit->getTimer()->getTicks() >= r_time))
	//	{
			//Valid target
			if (self->checkTarget())
			{
				//cout<<"comprobado"<<"   ";
				//Movement
				if (!self->onTarget()) //Not on target
				{
					//cout<<"no direccion"<<endl;
					self->turn(self->getDest()); //Turn
				}

				else //On target
				{
					//cout<<"direccion"<<endl;

					if (self->targetDist() <= self->getRange()) //Within range
					{
						s_flag = self->attack(); //Check attack timer
					}
					else //Move towards target
					{
						self->move();
					}
				}

				self->getTimer()->restart(); //Order timer
				return s_flag;
			}

			else //No target
			{
				self->setState(0); //Standby
				self->stop();
				return false;
			}
		}
		//else
		//{
		//	unit->turn();
		//}
	}

	default:
		break;
	}*/
	return s_flag;
}
