#include "Ship.h"
#include <cmath>
#include <iostream>

using namespace std;

Ship::Ship():MovingObject(TYPE_SHIP, SHIP_FIGHTER, 1) // <- change this
{
	setup(1);

	f_sel = false;
	m_sel_angle = 0;

	t_order.start();
	m_target = 0;
}

Ship::Ship(int subtype, int player, Vector2 center):MovingObject(TYPE_SHIP, subtype, player)
{
	setup(player);

	m_dir.x = 1;
	m_dir.y = 0;
	m_angle = 0;

	m_state = 0;

	f_sel = false;
	m_sel_angle = 0;


	setCen(center);
	setDest(center);
	stop();

	m_target = 0;
	center.y += m_size;
	b_health = new ProgressBar(0, center, m_health / m_max_health);
}

Ship::Ship(Texture *texture, int size, Texture *marktex, Vector2 cen2, int player):MovingObject(TYPE_SHIP, SHIP_FIGHTER, player)
{
	setup(player);

	m_dir.x = 1;
	m_dir.y = 0;
	m_angle = 0;

	//No destination
	m_dest.x = m_cen.x;
	m_dest.y = m_cen.y;

	//Stopped
	m_vel.makeZero();
	m_accel.makeZero();
	m_state = 0;

	f_sel = false;
	m_sel_angle = 0;

	setTex(texture);
	scaleTo(size);
	setMarker(marktex);
	setCen(cen2.x, cen2.y);
	m_player = player;

	t_order.start();

	m_target = 0;
	stop();
}

void Ship::setup(int player)
{
	//Selection marker color
	m_marker_color.r = 0x00;
	m_marker_color.g = 0xFF;
	m_marker_color.b = 0x00;
	m_marker_color.a = 0x00;

	switch (m_subtype)
	{
	case SHIP_FIGHTER:
	{
		//Movement
		m_max_accel = 0.2f;
		m_friction = 0.9f;
		m_steer_limit = 30;
		m_state = 0;
		m_sight = 250;

		//Health
		m_max_health = m_health = 5.0f;

		f_follow_mouse = false; //for funsies

		//Weapons
		v_stations = new StationVector;
		Weapon * w_minilaser = new Weapon(WEAPON_MINILASER, this);
		v_stations->add(w_minilaser);

		//Textures
		if (player == 1)
			setTex(&g_tex[0]); //Blue
		else
			setTex(&g_tex[8]); //Red

		scaleTo(SIZE_SMALL);
		setMarker(&g_tex[3]);

		break;
	}

	case BIG_SHIP:
	{
		//Movement
		m_max_accel = 0.15f;
		m_friction = 0.9f;
		m_steer_limit = 20;
		m_state = 0;
		m_sight = 400;

		//Health
		m_max_health = m_health = 20.0f;
		
		f_follow_mouse = false; //for funsies

		//Weapons
		v_stations = new StationVector;
		Weapon * w_laser = new Weapon(WEAPON_LASER, this);
		v_stations->add(w_laser);

		//Textures
		if (player == 1)
			setTex(&g_tex[0]); //Blue
		else
			setTex(&g_tex[8]); //Red

		scaleTo(SIZE_MEDIUM);
		setMarker(&g_tex[3]);
		break;
	}

	default:
		break;
	}
	
}

Ship::~Ship()
{
}

int Ship::event(SDL_Event* e, SDL_Rect m_sel, SDL_Point m)
{
	int accion = 0;

	//Box selection
	if (e->button.button == SDL_BUTTON_LEFT)
	{
		if (isInside(m_sel)) select();
		else deselect();
	}

	//Right click
	if ((e->type == SDL_MOUSEBUTTONDOWN) && (e->button.button == SDL_BUTTON_RIGHT) && (f_sel))
	{

		//Generate move command
		Command com = { MOVE_TO, Vector2(m.x, m.y) };

		//Add to list if shift is pressed
		if (g_keyboardState[SDL_SCANCODE_LSHIFT] || g_keyboardState[SDL_SCANCODE_RSHIFT])
		{
			l_commands.addCommand(com);
		}

		//Clear list if not pressed
		else
		{
			l_commands.replaceAll(com);
		}

		//setDest(m.x, m.y);
		setState(1);
		accion = 1;
	}

	if (f_follow_mouse)
	{
		//Generate move command
		Command com = { MOVE_TO, Vector2(m.x, m.y) };
		l_commands.replaceAll(com);

		setDest(m.x, m.y);
	}

	return accion;
}

Vector2 Ship::getPointyEnd()
{
	Vector2 aux;
	aux.x = m_cen.x + (m_tex->getDim().x / 2) * cos(m_angle*M_PI/180);
	aux.y = m_cen.y + (m_tex->getDim().y / 2) * sin(m_angle*M_PI/180);
	return aux;
}

float Ship::getRange()
{
	return m_range;
}

bool Ship::inRange(Vector2 p)
{
	return(m_cen.distance(p) <= m_range);
}

bool Ship::inRange(GameObject * s)
{
	return inRange(s->getCen());
}

bool Ship::inRange()
{
	return inRange(m_target);
}


float Ship::getSight()
{
	return m_sight;
}

bool Ship::inSight(Vector2 p)
{
	return(m_cen.distance(p) <= m_sight);
}

bool Ship::inSight(GameObject * s)
{
	return inSight(s->getCen());
}

bool Ship::inSight()
{
	return inSight(m_target);
}

void Ship::update()
{
	//Check for new commands
	if (l_commands.check())
	{
		m_command = l_commands.firstCommand();
	}

	bool f_done = false;

	//Follow command
	switch (m_command.type)
	{

		case NO_COMMAND:
		{

			break;
		}
	
		//Move command
		case MOVE_TO:
		{
			setDest(m_command.dest);

			if (abs(m_cen.distance(m_dest)) < 2 * m_size)
			{
				f_done = true;
			}
			break;
		}

		default:
			break;
	}

	//If command is done, get next command
	if (f_done)
	{
		l_commands.popFirst();
	}

	
	//Shoot
	setObjective();

	if (v_stations->count() > 0)
		v_stations->update();
}

void Ship::setObjective()
{
	//Shoot straight
	float dist = 200;
	Vector2 dist_aux = m_dir.normalize(dist);
	m_objective = m_cen + dist_aux;
}

bool Ship::attack()
{
	////Fire rate cap timer
	//if (t_shoot.isStarted() && (t_shoot.getSecs() > (1.0F / m_firerate)))
	//{
	//	t_shoot.restart();
	//	return true; //do the shootings
	//}
	//if (!t_shoot.isStarted())
	//{
	//	t_shoot.start();
	//	return false; //no shootings
	//}
	return false;
}

Vector2 Ship::shoot()
{
	Vector2 aux;
	aux.x = m_cen.x + m_dir.x * m_range;
	aux.y = m_cen.y + m_dir.y * m_range;
	return aux;
}

int Ship::getState()
{
	return m_state;
}

void Ship::setState(int s)
{
	m_state = s;
}

Timer * Ship::getTimer()
{
	return & t_order;
}

bool Ship::move() // -- testing new movement system --
{
	float m_slow_accel = m_max_accel / 1.5f;

	//If ship has a valid destination, go towards it
	if (m_dest != m_cen)
		m_accel = (m_dest - m_cen).normalize(m_max_accel); //update acceleration vector
	else
		m_accel.makeZero(); //If no valid destination, stop accelerating
	
	//If ship is ging really slow
	if (m_vel.length() < 1.0f)
	{
		m_accel = m_accel.aligned(m_dir);
	}
	
	//If near destination, slow down
	if (abs(m_cen.distance(m_dest)) < 2 * m_size)
		m_accel = m_accel.normalize(m_slow_accel);
	else
		m_accel = m_accel.normalize(m_max_accel);

	//Steering limit
	if (abs(m_dir.angle(m_accel)) > m_steer_limit)
	{
		if (m_dir.angle(m_accel) <= 0) //turn right
		{
			m_accel = m_accel.rotatedTo(m_dir.angle() - m_steer_limit);
		}
		else //turn left
		{
			m_accel = m_accel.rotatedTo(m_dir.angle() + m_steer_limit);
		}
	}

	m_vel = m_vel + m_accel; //update velocity vector
	m_vel = m_vel * m_friction; //reduce by friction factor
	setCen(m_cen + m_vel); //update position
	setAngle(m_vel.angle()); //update angle
	

	return false;
}


void Ship::setTarget(GameObject * t)
{
	m_target = t;
	m_dest = m_target->getCen();
}

void Ship::updateTarget()
{
	if (!m_target) return;
	else m_dest = m_target->getCen();
}

bool Ship::checkTarget()
{
	return m_target;
}

GameObject * Ship::getTarget()
{
	return m_target;
}

bool Ship::onTarget(Vector2 t, float err)
{
	Vector2 aux = t - m_cen;
	return (((int)abs(m_dir.angle() - aux.angle())%360 <= err) ||
			((int)abs(m_dir.angle() - aux.angle())%360 >= 360 - err));
}

bool Ship::onTarget(float err)
{
	if (!m_target) return false; //No target
	Vector2 aux = m_target->getCen() - m_cen;
	return (((int)abs(m_dir.angle() - aux.angle())%360 <= err) ||
		    ((int)abs(m_dir.angle() - aux.angle())%360 >= 360  -err));
}

float Ship::targetDist()
{
	if (!m_target) return m_cen.distance(m_dest);
	return m_cen.distance(m_target->getCen());
}

void Ship::render(Camera cam)
{
	MovingObject::render(cam);
	if (f_sel || g_f_debug)
	{
		b_health->setCen(m_cen.x, m_cen.y - m_size); //Update health bar
		b_health->setProgress(m_health / m_max_health);
		b_health->render(cam);
	}
}