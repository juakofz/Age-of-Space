#include "Player.h"

using namespace std;

Player::Player(void)
{
	oro=energia=1000;
	name="jugador";
}


Player::~Player(void)
{
}

void Player::setName(std::string nombre)
{
	name=nombre;
}

std::string Player::getName()
{
	return name;
}

void Player::getRecursos(std::stringstream recursos[])
{
	recursos[0].str( " " );
	recursos[0] << oro;
	//cout<< "oro:"<< oro<<'\n';
	recursos[1].str( " " );
	recursos[1] << energia;
	//cout<< "energia:"<< energia<<'\n';
	//cout<<recursos[0].str()<<'\n'<<recursos[1].str()<<'\n';
}