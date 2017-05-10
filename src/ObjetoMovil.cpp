#include "ObjetoMovil.h"


ObjetoMovil::ObjetoMovil(int t, bool selec):GameObject(t, selec)
{
	
	//Vector2 por defecto 0,0;
	//Dirección predeterminada
	dir.x = 1;
	dir.y = 0;
	angle = 0;
	//Destino nulo
	dest.x = cen.x;
	dest.y = cen.y;
	following = 0;

	//Velocidad máxima
	max_vel = 2;
	turn_rad = 10;

	//Nave parada
	vel.x = 0;
	vel.y = 0;

	sel = false;
	sel_angle = 0;

	tex = NULL;
}


ObjetoMovil::~ObjetoMovil()
{
}

int ObjetoMovil::event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m)
{
	
	//Selección múltiple
	if (e->button.button == SDL_BUTTON_LEFT)
	{
		if (((cen.x > m_sel.x - tex->getDim().x/2) && (cen.x < (m_sel.x + m_sel.w + tex->getDim().x / 2))))
		{
			if (((cen.y > m_sel.y - tex->getDim().y / 2) && (cen.y < (m_sel.y + m_sel.h + tex->getDim().y / 2))))
			{
				select();
			}
			else deselect();
		}
		else deselect();
	}


	//Botón derecho (movimiento)
	if ((e->type == SDL_MOUSEBUTTONDOWN) && (e->button.button == SDL_BUTTON_RIGHT) && (sel))
	{
		//SDL_GetMouseState(&mx, &my);
		dest.x = m.x;
		dest.y = m.y;

		//Dirección
		dir.x = dest.x - cen.x;
		dir.y = dest.y - cen.y;

		angle = (180 * atan2(dir.y, dir.x) / M_PI);
	}
	return 0;

}

void ObjetoMovil::render(Camera cam)
{
	GameObject::render(cam);
}

bool ObjetoMovil::move()
{
	//Dirección
	dir.x = dest.x - cen.x;
	dir.y = dest.y - cen.y;

	angle = (180 * atan2(dir.y, dir.x) / M_PI);
	

	//Movimiento rectilíneo
	if ((abs(cen.x - dest.x) > max_vel) || (abs(cen.y - dest.y) > max_vel)) {

		//Ajuste de velocidades
		vel.x = max_vel * cos(M_PI * angle / 180);
		vel.y = max_vel * sin(M_PI * angle / 180);
		
		//Movimiento
		SetCen(cen.x + vel.x, cen.y + vel.y);
	}
	else
	{
		vel.x = 0;
		vel.y = 0;
	}

	return false();
}

bool ObjetoMovil::turn(int x, int y)
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

	if(angle>360) angle-=360;
	if(angle<0) angle +=360;

	double vel_ang = max_vel / turn_rad;
	Vector2 posrel;
	Vector2 cen_cir;
	posrel = dest - cen;
	float ang_rel=posrel.argumento();
	//eleccion de centro

	if ((abs(cen.x - dest.x) > max_vel) || (abs(cen.y - dest.y) > max_vel)) 
	{

		flag=false;
	//cout<<posrel.x<<","<<posrel.y<<endl;
	//cout<<ang_rel<<"   "<<angle<<endl;



	if(ang_rel>(angle-2) && ang_rel<(angle+2))
	{
			//cout<<"dentro"<<endl;
			move();
	}
		
	else
	{
	if((int)ang_rel%360<180 && (int)ang_rel%360>0)
	{

		cen_cir.x = turn_rad * cos(((90-angle)*M_PI/180)) + cen.x;
		cen_cir.y = cen.y - turn_rad * sin(((90-angle)*M_PI/180));
		angle -= vel_ang*180/M_PI;
	}
	else
	{
		angle += vel_ang*180/M_PI;
		
	}



	//movimiento circul

	//Ajuste de velocidades
		vel.x = max_vel * cos(M_PI * angle / 180);
		vel.y = max_vel * sin(M_PI * angle / 180);
		
		//Movimiento
		SetCen(cen.x + vel.x, cen.y + vel.y);
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

void ObjetoMovil::stop()
{
	dest.x = cen.x;
	dest.y = cen.y;
	vel.x = 0;
	vel.y = 0;
}

bool ObjetoMovil::moveTo(int x, int y)
{
	//vel.x = dir.x;
	//vel.y = dir.y;
	dest.x = x;
	dest.y = y;

	dir.x = dest.x - cen.x;
	dir.y = dest.y - cen.y;

	angle = (180 * atan2(dir.y, dir.x) / M_PI);
	return false;
}



Vector2& ObjetoMovil::getDest()
{
	following=true;
	return dest;

}

//Velocidad
Vector2 ObjetoMovil::GetVel()
{
	return vel;
}

void ObjetoMovil::SetVel(float x, float y)
{
	vel.x = x;
	vel.y = y;
}

void ObjetoMovil::SetMaxVel(float v)
{
	max_vel = v;
}
//Dirección
Vector2 ObjetoMovil::GetDir()
{
	return dir;
}

void ObjetoMovil::SetDir(float x, float y)
{
	dir.x = x;
	dir.y = y;
}

void ObjetoMovil::setDest(float x, float y)
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

bool ObjetoMovil::onPoint(Vector2 p)
{
	if (cen.distancia(p) < max_vel) return true;
	else return false;
}

bool ObjetoMovil::onDest()
{
	return onPoint(dest);
}