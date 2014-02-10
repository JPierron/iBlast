#include "Shoot.h"

Shoot::Shoot(const std::string& play, float x, float y, int bonus) : Entities(IBLAST::_POS_SHOT, "")
{
	img.LoadFromFile("ressources/shot.png");
	name_play = play;
	sprite.SetImage(img);
	pos.x = x;
	pos.y = y;
	sprite.SetX(x);
	sprite.SetY(y);
	timer = 0;
	speed = bonus;
	id_t = shoot++;
}

Shoot::~Shoot()
{
}

void			Shoot::playEvent(Plat&)
{
	this->Move();
}

sf::Drawable*	Shoot::getEntities()
{
	return &this->sprite;
}

void			Shoot::Move()
{
	this->timer++;
	if (this->speed == 1)
		this->pos.y += 1;
	if (this->speed == 2)
		this->pos.y -= 1;
	this->pos.x += 3;
	this->sprite.SetX(this->pos.x);
	this->sprite.SetY(this->pos.y);
}

float Shoot::getPosX()
{
	return this->pos.x;
}

float Shoot::getPosY()
{
	return this->pos.y;
}

sf::Sprite Shoot::getSprite()
{
	return this->sprite;
}

int	Shoot::getLife()
{
	return (0);
}

void	Shoot::setLife(int life)
{
}

int		Shoot::getIdT()
{
	return this->id_t;
}

int		Shoot::getIdMob()
{
	return 0;
}

std::string		Shoot::getPlayName()
{
	return this->name_play;
}

void		Shoot::setPos(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
}