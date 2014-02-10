#include "Pepel.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Pepel::Pepel() : Entities(PEPELOUNI, "")
{
	id_t = pepelouni++;
	img.LoadFromFile("Ressources/pepel.png");
	sprite.SetImage(img);
	pos.x = 800;
	pos.y = 200;
	slim_fire = 50;
	lim_fire = 50;
	coef = -1;
}

Pepel::~Pepel()
{
}

void	Pepel::playEvent(Plat& cli)
{
	if (this->lim_fire > 0)
	this->lim_fire--;
	if (this->lim_fire == 0)
	{
		cli.getWManager().newEntities(new ShootMob(this->id_t, this->pos.x-50,this->pos.y+50, 1));
		this->lim_fire = this->slim_fire;
	}
	this->Move();
}

sf::Drawable*	Pepel::getEntities()
{
	return &this->sprite;
}

void	Pepel::getState()
{
	if (this->state >= 2)
		this->state = 0;
	else
		this->state++;
}

void	Pepel::Move()
{
	if (this->pos.x + 250 != 800)
		this->pos.x--;
	else
		this->pos.y += 1 * this->coef;
	if (this->pos.y == 5)
		this->coef = 1;
	if (this->pos.y == 280)
		this->coef = -1;
	this->sprite.SetX(this->pos.x);
	this->sprite.SetY(this->pos.y);
}

float Pepel::getPosX()
{
	return this->pos.x;
}

float Pepel::getPosY()
{
	return this->pos.y;
}

sf::Sprite Pepel::getSprite()
{
	return this->sprite;
}

int	Pepel::getLife()
{
	return this->life;
}

void	Pepel::setLife(int _life)
{
	this->life = _life;
}

int		Pepel::getIdT()
{
	return this->id_t;
}

int		Pepel::getIdMob()
{
	return 0;
}

std::string		Pepel::getPlayName()
{
	return "";
}

void		Pepel::setPos(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
}
