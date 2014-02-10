#ifndef _DEFBACK_
#define _DEFBACK_
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Plat.h"
#include "Entities.h"

static int defback = 0;
class DefBack
	: public Entities
{
	int					id_t;
	sf::Image			img;
	sf::Sprite			sprite;
	sf::Vector2<float>	pos;
public:
	DefBack(float, float);
	~DefBack();
	void			playEvent(Plat&);
	sf::Drawable*	getEntities();
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