	#ifndef _Pepel_
#define _Pepel_
#include <iostream>
#include "Entities.h"
#include "Plat.h"
#include "ShootMob.h"

class Plat;
class ShootMob;
class Entities;
static int pepelouni = 0;
class Pepel
	: public Entities
{
	int						id_t;
	int						coef;
	int						state;
	int						dir;
	int						lim_fire;
	int						slim_fire;
	int						life;
	sf::Vector2<float>		pos;
	sf::Image				img;
	sf::Sprite				sprite;
public:
	Pepel(int, int, float, float);
	Pepel();
	~Pepel();
	void			playEvent(Plat&);
	sf::Drawable*	getEntities();
	void			getState();
	void			Move();
	float			getPosX();
	float			getPosY();
	sf::Sprite		getSprite();
	int				getLife();
	void			setLife(int);
	int				getIdT();
	int				getIdMob();	
	std::string		getPlayName();
	void			setPos(float, float);

};

#endif