#include "ShootMob.h"

ShootMob::ShootMob(int _id_mob, float x, float y, int i) : Entities(IBLAST::_POS_SHOT_MOB, "")
{
	id_mob = _id_mob;
	if (i == 1)
		img.LoadFromFile("ressources/pepelshot.png");
	else
		img.LoadFromFile("ressources/mobshot.png");
	sprite.SetImage(img);
	pos.x = x;
	pos.y = y;
	sprite.SetX(x);
	sprite.SetY(y);
	coef = rand() % 6;
	if (coef == 2 || coef == 4)
		coef *= -1;
	id_t = shootmob++;
}

ShootMob::~ShootMob()
{
}

void			ShootMob::playEvent(Plat&)
{
	this->Move();
}

sf::Drawable*	ShootMob::getEntities()
{
	return &this->sprite;
}

void	ShootMob::Move()
{
	this->pos.x -= 1;
	this->pos.y += 1 * coef;
	this->sprite.SetX(this->pos.x);
	this->sprite.SetY(this->pos.y);
}

float ShootMob::getPosX()
{
	return this->pos.x;
}

float ShootMob::getPosY()
{
	return this->pos.y;
}

sf::Sprite ShootMob::getSprite()
{
	return this->sprite;
}

int	ShootMob::getLife()
{
	return (0);
}

void	ShootMob::setLife(int life)
{
}

int		ShootMob::getIdT()
{
	return this->id_t;
}

int		ShootMob::getIdMob()
{
	return id_mob;
}

std::string		ShootMob::getPlayName()
{
	return "";
}

void		ShootMob::setPos(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
}

