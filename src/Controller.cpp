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

bool Controller::agressive(int ind)
{
	if (!naves) return false;

	int r_time = 1000; //Order time
	bool s_flag = false; //Shoot flag

	Ship * unit = naves->getShip(ind);
	if (!unit) return false;

	//std::cout<<unit->getState()<<endl;

	//State machine: 0 = standby, 1 = moving, 2 = attacking 
	switch (unit->getState())
	{

	case 0: //Stand by
	{
		//Order time = 0.5 s
		if (unit->getTimer()->isStarted() && (unit->getTimer()->getTicks() <= r_time / 2))
			{
				return false;
				break;
		}
		//cout<<"1"<<endl;
		else
		{

		//Targetting
		for (int i = (naves->getSize() - 1); i >= 0; i--)
		{
			Ship *nave = naves->getShip(i);
			//cout<<naves->getPlayer(i)<<endl;
			if (naves->getPlayer(i) != unit->getPlayer()) //Different players
			{
				//cout<<"2"<<endl;
				if (unit->inSight(naves->getCen(i))) //Within sight
				{

					//cout<<"target"<<endl;
					unit->setTarget(naves->getShip(i)); //Target acquired

					//Movement
					if (!(unit->onTarget(naves->getShip(i)->GetCen()))) //Not on target
					{
						//cout<<"prueba2"<<endl;
						unit->turn(unit->getDest()); //Turn
					}

					else //On target
					{
						//cout<<"prueba1"<<endl;
						if (unit->inRange(naves->getCen(i))) //Within range
						{
							s_flag = unit->attack(); //Check attack timer
						}
						else //Move towards target
						{
							unit->move();
						}
					}
					unit->getTimer()->restart(); //Order timer
					unit->setState(2); //Switch to attacking
					//cout<<s_flag<<endl;
					return s_flag;
				}
			}
		}
		}
		return false;
		break;
	}

	case 1: //Moving (direct order)
	{
		//Reached destination
		if (unit->onDest())
		{
			unit->setState(0); //Standby
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
				if(unit->turn()) unit->setState(0);
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
			if (unit->checkTarget())
			{
				//cout<<"comprobado"<<"   ";
				//Movement
				if (!unit->onTarget()) //Not on target
				{
					//cout<<"no direccion"<<endl;
					unit->turn(unit->getDest()); //Turn
				}

				else //On target
				{
					//cout<<"direccion"<<endl;

					if (unit->targetDist() <= unit->getRange()) //Within range
					{
						s_flag = unit->attack(); //Check attack timer
					}
					else //Move towards target
					{
						unit->move();
					}
				}

				unit->getTimer()->restart(); //Order timer
				return s_flag;
			}

			else //No target
			{
				unit->setState(0); //Standby
				unit->stop();
				return false;
			}
	/*	}
		else
		{
			unit->turn();
		}*/
	}

	default:
		break;
	}
	return s_flag;
}
