#include "Player.h"

using namespace std;

Player::Player(void)
{
	oro=energia=100;
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

bool Player::cambiarRecursos(int oro_cambio, int energia_cambio)
{
	if((((oro * energia) == 0) && ((oro_cambio < 0) || (energia_cambio < 0 ))) || (((oro + oro_cambio) < 0 ) || ((energia + energia_cambio) < 0))) return true;
	//cout<<oro<<" mas "<<oro_cambio<<endl;
	// cout<<oro + oro_cambio<<" en el if" <<endl;
	if((oro + oro_cambio) < 0 );
	((oro+oro_cambio)>=0)?(oro+=oro_cambio):0;
	((energia+energia_cambio)>=0)?(energia+=energia_cambio):0;
	//energia+=energia_cambio;
	return false;
	
}