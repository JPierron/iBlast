#include "MazzelTof.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

MazzelTof::MazzelTof(int _dir, int _lim_fire, float _pos_x, float _pos_y) : Entities(IBLAST::_POS_ENN_I, "")
{
	id_t = mazzeltof++;
	img.LoadFromFile("Ressources/mazzel.png");
	sprite.SetImage(img);
	pos.x = _pos_x;
	pos.y = _pos_y;
	slim_fire = _lim_fire;
	lim_fire = _lim_fire;
	dir = _dir;
	state = 0;
}

MazzelTof::~MazzelTof()
{
}

void	MazzelTof::playEvent(Plat& cli)
{
	if (this->lim_fire > 0)
	this->lim_fire--;
	if (this->lim_fire == 0)
	{
		cli.getWManager().newEntities(new ShootMob(this->id_t, this->pos.x-35,this->pos.y,0));
		this->lim_fire = this->slim_fire;
	}
	this->Move();
}

sf::Drawable*	MazzelTof::getEntities()
{
	return &this->sprite;
}

void	MazzelTof::getState()
{
	if (this->state >= 2)
		this->state = 0;
	else
		this->state++;
}

void	MazzelTof::Move()
{
	this->getState();
	int coef =  rand() % 100;
	int coef2 = rand() % 2;
	this->sprite.SetSubRect(sf::IntRect(this->state * 34, 0 * 34,(this->state + 1) * 34, (0 + 1) * 34));
	if (coef < 50 && pos.y < 480)
		this->pos.y += 1;
	else 
		if (this->pos.y > 100)
			this->pos.y -= 1;
	this->pos.x--;
	this->sprite.SetX(this->pos.x);
	this->sprite.SetY(this->pos.y);
}

float MazzelTof::getPosX()
{
	return this->pos.x;
}

float MazzelTof::getPosY()
{
	return this->pos.y;
}

sf::Sprite MazzelTof::getSprite()
{
	return this->sprite;
}

int	MazzelTof::getLife()
{
	return 0;
}

void	MazzelTof::setLife(int)
{
}

int		MazzelTof::getIdT()
{
	return this->id_t;
}

int		MazzelTof::getIdMob()
{
	return 0;
}

std::string		MazzelTof::getPlayName()
{
	return "";
}

void		MazzelTof::setPos(float x, float y)
{
	if (this->pos.x == 0 && this->pos.y == 0)
	{
		this->pos.x = this->getTMPx();
		this->pos.y = this->getTMPy();
	}
	else
	{
		this->pos.x = x;
		this->pos.y = y;
	}
	
}
