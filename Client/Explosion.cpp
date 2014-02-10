#include "Explosion.h"

Explosion::Explosion(float x, float y) : Entities(EXPLOSION, "")
{
	id_t = explosion++;
	img.LoadFromFile("ressources/boom.png");
	sprite.SetImage(img);
	sprite.SetSubRect(sf::IntRect(3 * 30, 0 * 33,(3 + 1) * 30, (0 + 1) * 33));
	pos.x = x;
	pos.y = y;
	sprite.SetX(x);
	sprite.SetY(y);
	time = 0;
	state = 3;
	end = 0;
}

Explosion::~Explosion()
{
}

void			Explosion::playEvent(Plat&)
{
	this->time++;
	if (this->time == 10)
	{
		this->time = 0;	
		this->state--;
	}	
	sprite.SetSubRect(sf::IntRect(this->state * 30, 0 * 33,(this->state + 1) * 30, (0 + 1) * 33));
	if (this->state == 0)
		this->end = 1;
}

sf::Drawable*	Explosion::getEntities()
{
	return &this->sprite;
}

float Explosion::getPosX()
{
	return this->pos.x;
}

float Explosion::getPosY()
{
	return this->pos.y;
}

sf::Sprite Explosion::getSprite()
{
	return this->sprite;
}

int	Explosion::getLife()
{
	return this->end;
}

void	Explosion::setLife(int life)
{
}
int		Explosion::getIdT()
{
	return this->id_t;
}

int		Explosion::getIdMob()
{
	return 0;
}

std::string		Explosion::getPlayName()
{
	return "";
}

void		Explosion::setPos(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
}