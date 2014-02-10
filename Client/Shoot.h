#ifndef _SHOOT_
#define _SHOOT_
#include "Entities.h"
#include "Plat.h"

static int shoot = 1;
class Shoot
	: public Entities
{
	int					id_t;
	std::string			name_play;
	int					speed;
	int					timer;
	sf::Image			img;
	sf::Sprite			sprite;
	sf::Vector2<float>	pos;
public:   
	Shoot(const std::string&, float, float, int);
	~Shoot();
	void			playEvent(Plat&);
	sf::Drawable*	getEntities();
	int				getLife();
	void			Move();
	float			getPosX();
	float			getPosY();
	sf::Sprite		getSprite();
	void			setLife(int);
	int				getIdT();
	int				getIdMob();	
	void			setPos(float, float);
	std::string		getPlayName();

};

#endif