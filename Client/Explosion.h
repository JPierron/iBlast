#ifndef _EXPLOSION_
#define _EXPLOSION_
#include "Entities.h"
#include "Plat.h"

static int explosion = 0;
class Explosion
	: public Entities
{
	int					id_t;
	int					time;
	int					state;
	int					end;
	sf::Image			img;
	sf::Sprite			sprite;
	sf::Vector2<float>	pos;
public:   
	Explosion(float, float);
	~Explosion();
	void			playEvent(Plat&);
	sf::Drawable*	getEntities();
	int				getLife();
	float			getPosX();
	float			getPosY();
	sf::Sprite		getSprite();
	void			setLife(int);
	int				getIdT();
	int				getIdMob();
	std::string		getPlayName();
	void			setPos(float, float);

};

#endif