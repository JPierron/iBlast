#ifndef _MazzelTof_
#define _MazzelTof_
#include <iostream>
#include "Entities.h"
#include "Plat.h"
#include "ShootMob.h"
class Plat;
class ShootMob;
class Entities;
static int mazzeltof = 1;
class MazzelTof
	: public Entities
{
	int						id_t;
	int						state;
	int						dir;
	int						lim_fire;
	int						slim_fire;
	sf::Vector2<float>		pos;
	sf::Image				img;
	sf::Sprite				sprite;
public:
	MazzelTof(int, int, float, float);
	MazzelTof();
	~MazzelTof();
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