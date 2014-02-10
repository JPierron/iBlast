#include "DefBackground.h"

DefBack::DefBack(float _pos_x, float _pos_y) : Entities(BACKG, "")
{
	id_t = defback++;
	img.LoadFromFile("ressources/fond.png");
	sprite.SetImage(img);
	pos.x = _pos_x;
	pos.y = _pos_y;
}

DefBack::~DefBack()
{
}

void	DefBack::playEvent(Plat& cli)
{
	this->Move();
}

sf::Drawable*	DefBack::getEntities()
{
	return &this->sprite;
}

void	DefBack::Move()
{
	if (this->pos.x == -800)
		this->pos.x = 800;
	this->pos.x -= (float)0.1;
	this->sprite.SetX(this->pos.x);
	this->sprite.SetY(this->pos.y);
}

float DefBack::getPosX()
{
	return this->pos.x;
}

float DefBack::getPosY()
{
	return this->pos.y;
}

sf::Sprite DefBack::getSprite()
{
	return this->sprite;
}

int	DefBack::getLife()
{
	return (0);
}

void	DefBack::setLife(int life)
{
}

int		DefBack::getIdT()
{
	return this->id_t;
}

int		DefBack::getIdMob()
{
	return 0;
}

std::string		DefBack::getPlayName()
{
	return "";
}

void		DefBack::setPos(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
}
