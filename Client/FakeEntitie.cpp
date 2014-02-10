#include "FakeEntitie.h"

FakeEntitie::FakeEntitie(int _id_t, int _type, std:: string _name, int _type_shot) : Entities(_type, _name)
{
	id_t = _id_t;
	type = _type;
	name = _name;
	type_shot = _type_shot;
	PtrMeth.insert(std::make_pair(IBLAST::_POS_HERO, &FakeEntitie::doHero));
	PtrMeth.insert(std::make_pair(IBLAST::_POS_ENN_I, &FakeEntitie::doMazzelTof));
	PtrMeth.insert(std::make_pair(IBLAST::_POS_ENN_II, &FakeEntitie::doPepelouni));
	PtrMeth.insert(std::make_pair(IBLAST::_POS_SHOT, &FakeEntitie::doShot));
	PtrMeth.insert(std::make_pair(IBLAST::_POS_SHOT_MOB, &FakeEntitie::doShotMob));
	for (std::map<int, PtrFake>::iterator it = PtrMeth.begin(); it != PtrMeth.end(); it++)
	{
		if (it->first == type)
		{
			PtrFake ptr = it->second;
			(this->*ptr)();
		}
	}
}
FakeEntitie::~FakeEntitie()
{
}


void	FakeEntitie::doHero()
{
	this->img.LoadFromFile("ressources/princ.png");
	this->sprite.SetImage(img);
	this->sprite.SetSubRect(sf::IntRect(3 * 33, 1 * 17,(3 + 1) * 33, (1 + 1) * 17));
}

void	FakeEntitie::doMazzelTof()
{
	this->img.LoadFromFile("Ressources/mazzel.png");
	this->sprite.SetImage(img);
	this->sprite.SetSubRect(sf::IntRect(1 * 34, 0 * 34,(1 + 1) * 34, (0 + 1) * 34));
}

void	FakeEntitie::doPepelouni()
{
	this->img.LoadFromFile("Ressources/pepel.png");
	this->sprite.SetImage(img);
}

void	FakeEntitie::doShot()
{
	this->img.LoadFromFile("ressources/shot.png");
	this->sprite.SetImage(img);
}

void	FakeEntitie::doShotMob()
{
	if (this->type_shot == 1)
		this->img.LoadFromFile("ressources/pepelshot.png");
	else
		this->img.LoadFromFile("ressources/mobshot.png");
	this->sprite.SetImage(img);
}

void	FakeEntitie::setPos(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
}

void			FakeEntitie::playEvent(Plat&)
{
	this->sprite.SetX(this->pos.x);
	this->sprite.SetY(this->pos.y);
}

sf::Drawable*	FakeEntitie::getEntities()
{
	return &this->sprite;
}

int				FakeEntitie::getLife()
{
	return this->life;
}

float			FakeEntitie::getPosX()
{
	return this->pos.x;
}

float			FakeEntitie::getPosY()
{
	return this->pos.y;
}

sf::Sprite		FakeEntitie::getSprite()
{
	return this->sprite;
}

void			FakeEntitie::setLife(int _life)
{
	this->life = _life;
}

int				FakeEntitie::getIdT()
{
	return this->id_t;
}

int				FakeEntitie::getIdMob()
{
	return 0;
}

std::string		FakeEntitie::getPlayName()
{
	return name;
}