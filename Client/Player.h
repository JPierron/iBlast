	#ifndef _PLAYER_
#define _PLAYER_
#include <iostream>
#include "Entities.h"
#include "Plat.h"
#include "Shoot.h"
class Player;
typedef void (Player::*PtrInput)(Plat&);

class Plat;
class Entities;
class EntitiesManager;
class Shoot;
static int player = 0;
class Player
	: public Entities
{
	std::string				name;
	int						id_t;
	void			setPos(float, float);
	int						life;
	int						pts;
	int						power_up;
	int						state;
	int						tmp_state;
	int						lim_fire;
	sf::Vector2<float>		pos;
	sf::Image				img;
	sf::Sprite				sprite;
	std::map<int,PtrInput>	PtrMeth;
public:
	Player(std::string, float, float);
	Player();
	~Player();
	void			playEvent(Plat&);
	sf::Drawable*	getEntities();
	void			getState();
	void			Move();
	float			getPosX();
	float			getPosY();
	int				getLife();
	void			setLife(int);
	void			doKeyUp(Plat&);
	void			doKeyDown(Plat&);
	void			doKeyLeft(Plat&);
	void			doKeyRight(Plat&);
	void			doKeySpace(Plat&);
	void			doKeyR(Plat&);
	sf::Sprite		getSprite();
	int				getIdT();
	int				getIdMob();	
	std::string		getPlayName();

};

#endif