#ifndef _SHOOTMOB_
#define _SHOOTMOB_
#include "Entities.h"
#include "Plat.h"

class Plat;
class Entities;
static int shootmob = 0;
class ShootMob
	: public Entities
{
	int					id_t;
	int					id_mob;
	int					coef;
	sf::Image			img;
	sf::Sprite			sprite;
	sf::Vector2<float>	pos;
public:   
	ShootMob(int, float, float, int);
	~ShootMob();
	void			playEvent(Plat&);
	sf::Drawable*	getEntities();
	int				getLife();
	void			Move();
	void			setLife(int);
	float			getPosX();
	float			getPosY();
	sf::Sprite		getSprite();
	int				getIdT();
	int				getIdMob();
	void			setPos(float, float);
	std::string		getPlayName();
};

#endif