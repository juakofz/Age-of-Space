#include "MovingObject.h"


MovingObject::MovingObject(int type, int player):GameObject(type, player)
{
	//No rotation
	dir.x = 1;
	dir.y = 0;
	m_angle = 0;
	
	//No destination
	dest.x = cen.x;
	dest.y = cen.y;
	following = 0;

	//Velocidad máxima
	max_vel = 2;
	turn_rad = 10;

	//Nave parada
	vel.x = 0;
	vel.y = 0;

	f_sel = false;
	m_sel_angle = 0;

	m_tex = NULL;
}


MovingObject::~MovingObject()
{
}

int MovingObject::event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m)
{
	
	//Selección múltiple
	if (e->button.button == SDL_BUTTON_LEFT)
	{
		if (((cen.x > m_sel.x - m_tex->getDim().x/2) && (cen.x < (m_sel.x + m_sel.w + m_tex->getDim().x / 2))))
		{
			if (((cen.y > m_sel.y - m_tex->getDim().y / 2) && (cen.y < (m_sel.y + m_sel.h + m_tex->getDim().y / 2))))
			{
				select();
			}
			else deselect();
		}
		else deselect();
	}


	//Botón derecho (movimiento)
	if ((e->type == SDL_MOUSEBUTTONDOWN) && (e->button.button == SDL_BUTTON_RIGHT) && (f_sel))
	{
		//SDL_GetMouseState(&mx, &my);
		dest.x = m.x;
		dest.y = m.y;

		//Dirección
		dir.x = dest.x - cen.x;
		dir.y = dest.y - cen.y;

		m_angle = (180 * atan2(dir.y, dir.x) / M_PI);
	}
	return 0;

}

void MovingObject::render(Camera cam)
{
	GameObject::render(cam);
}

bool MovingObject::move()
{
	//Dirección
	dir.x = dest.x - cen.x;
	dir.y = dest.y - cen.y;

	m_angle = (180 * atan2(dir.y, dir.x) / M_PI);
	

	//Movimiento rectilíneo
	if ((abs(cen.x - dest.x) > max_vel) || (abs(cen.y - dest.y) > max_vel)) {

		//Ajuste de velocidades
		vel.x = max_vel * cos(M_PI * m_angle / 180);
		vel.y = max_vel * sin(M_PI * m_angle / 180);
		
		//Movimiento
		setCen(cen.x + vel.x, cen.y + vel.y);
	}
	else
	{
		vel.x = 0;
		vel.y = 0;
	}
	return false;
}

bool MovingObject::turn(int x, int y)
{
	
/*	int turn_error = 1;

	float a_n = (max_vel * max_vel) / turn_rad;
	float compl;

	Vector2 aux(x - cen.x, y - cen.y);
	float angle_dest = aux.argumento();

	(angle <= 180) ? compl = angle + 180 : compl = angle - 180;
	
//	if(angle > )

	if (angle <= 180)
	{
		compl = angle + 180;
		if ((angle_dest < angle) ||(angle_dest > compl))
		{
			//turn left
			accel.x = - dir.y * a_n;
			accel.y = dir.x * a_n;
		}
		else
		{
			//turn right
			accel.x = dir.y * a_n;
			accel.y = -dir.x * a_n;
		}
	}
	else
	{
		compl = angle - 180;
		if ((angle_dest > angle) || (angle_dest < compl))
		{
			//turn right
			accel.x = dir.y * a_n;
			accel.y = -dir.x * a_n;
		}
		else
		{
			//turn left
			accel.x = -dir.y * a_n;
			accel.y = dir.x * a_n;
		}
	}*/

	/*
	if (abs(angle - aux.argumento()) < turn_error) //Ok
		return true;
	else
	{
		if ((angle - aux.argumento()) >= turn_error) //Izquierda
		{
			accel.x = -dir.y * a_n;
			accel.y = dir.x * a_n;
		}
		if ((angle - aux.argumento()) <= turn_error) //derecha
		{
			accel.x = dir.y * a_n;
			accel.y = -dir.x * a_n;
		}
		
		if ((vel.x == 0) && (vel.y == 0))
		{
			vel.x = max_vel * dir.x;
			vel.y = max_vel * dir.y;
		}
		*/
		//Mover
	/*	vel.x += accel.x;
		vel.y += accel.y;

		dir = vel.norm();
		angle = dir.argumento();

		SetPos(pos.x += vel.x, pos.y += vel.y);
		
		return false;*/

	//METODO CHERIPERI

	bool flag;

	if(m_angle>360) m_angle-=360;
	if(m_angle<0) m_angle +=360;

	double vel_ang = max_vel / turn_rad;
	Vector2 posrel;
	Vector2 cen_cir;
	posrel = dest - cen;
	float ang_rel=posrel.angle();
	//eleccion de centro

	if ((abs(cen.x - dest.x) > max_vel) || (abs(cen.y - dest.y) > max_vel)) 
	{

		flag=false;
	//cout<<posrel.x<<","<<posrel.y<<endl;
	//cout<<ang_rel<<"   "<<angle<<endl;



	if(ang_rel>(m_angle-2) && ang_rel<(m_angle+2))
	{
			//cout<<"dentro"<<endl;
			move();
	}
		
	else
	{
	if((int)ang_rel%360<180 && (int)ang_rel%360>0)
	{

		cen_cir.x = turn_rad * cos(((90- m_angle)*M_PI/180)) + cen.x;
		cen_cir.y = cen.y - turn_rad * sin(((90- m_angle)*M_PI/180));
		m_angle -= vel_ang*180/M_PI;
	}
	else
	{
		m_angle += vel_ang*180/M_PI;
		
	}



	//movimiento circul

	//Ajuste de velocidades
		vel.x = max_vel * cos(M_PI * m_angle / 180);
		vel.y = max_vel * sin(M_PI * m_angle / 180);
		
		//Movimiento
		setCen(cen.x + vel.x, cen.y + vel.y);
	}
	}
	else
	{
		vel.x=0;
		vel.y=0;
		flag=true;
	}

	return flag;
}

void MovingObject::stop()
{
	dest.x = cen.x;
	dest.y = cen.y;
	vel.x = 0;
	vel.y = 0;
}

bool MovingObject::moveTo(int x, int y)
{
	//vel.x = dir.x;
	//vel.y = dir.y;
	dest.x = x;
	dest.y = y;

	dir.x = dest.x - cen.x;
	dir.y = dest.y - cen.y;

	m_angle = (180 * atan2(dir.y, dir.x) / M_PI);
	return false;
}



Vector2& MovingObject::getDest()
{
	following=true;
	return dest;

}

//Velocidad
Vector2 MovingObject::GetVel()
{
	return vel;
}

void MovingObject::SetVel(float x, float y)
{
	vel.x = x;
	vel.y = y;
}

void MovingObject::SetMaxVel(float v)
{
	max_vel = v;
}
//Dirección
Vector2 MovingObject::GetDir()
{
	return dir;
}

void MovingObject::SetDir(float x, float y)
{
	dir.x = x;
	dir.y = y;
}

void MovingObject::setDest(float x, float y)
{
	//Destino
	dest.x = x;
	dest.y = y;

	/*//Dirección
	dir.x = dest.x - cen.x;
	dir.y = dest.y - cen.y;

	//Angulo
	angle = (180 * atan2(dir.y, dir.x) / M_PI);*/
}

bool MovingObject::onPoint(Vector2 p)
{
	if (cen.distance(p) < max_vel) return true;
	else return false;
}

bool MovingObject::onDest()
{
	return onPoint(dest);
}