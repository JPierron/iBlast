#include "Player.h"

Player::Player(std::string _name, float _pos_x, float _pos_y) : Entities(PLAYER, _name)
{
	power_up = 1;
	id_t = player++;
	img.LoadFromFile("ressources/princ.png");
	sprite.SetImage(img);
	sprite.SetSubRect(sf::IntRect(3 * 33, 1 * 17,(3 + 1) * 33, (1 + 1) * 17));
	name = _name;
	pos.x = _pos_x;
	pos.y = _pos_y;
	life = 5;
	pts = 0;
	lim_fire = 0;
	PtrMeth.insert(std::make_pair(IBLAST::KeyUp, &Player::doKeyUp));	
	PtrMeth.insert(std::make_pair(IBLAST::KeyDown, &Player::doKeyDown));	
	PtrMeth.insert(std::make_pair(IBLAST::KeyLeft, &Player::doKeyLeft));	
	PtrMeth.insert(std::make_pair(IBLAST::KeyRight, &Player::doKeyRight));
	PtrMeth.insert(std::make_pair(IBLAST::KeySpace, &Player::doKeySpace));
	PtrMeth.insert(std::make_pair(IBLAST::KeyR, &Player::doKeyR));
}

Player::~Player()
{
}

void	Player::doKeyDown(Plat& cli)
{
	if (this->pos.y < IBLAST::HEIGHT - 17 - IBLAST::BLIFE)
	{
		this->pos.y+=2;
		this->state = -1;
	}
}

void	Player::doKeyLeft(Plat& cli)
{
	if (this->pos.x > 0)
		this->pos.x-=2;	
}

void	Player::doKeyRight(Plat& cli)
{
	if (this->pos.x < IBLAST::WIDTH - 33)
		this->pos.x+=2;
}

void	Player::doKeyUp(Plat& cli)
{
	if (this->pos.y > 0)
	{
		this->pos.y -= 2;
		this->state = 1;
	}
}

void	Player::doKeySpace(Plat& cli)
{
	if (this->lim_fire == 0)
	{
		cli.getWManager().newEntities(new Shoot(this->name, this->pos.x+34,this->pos.y, 0));
		this->lim_fire = 20;
	}
}

void	Player::doKeyR(Plat& cli)
{
	if (this->lim_fire == 0 && this->power_up > 0)
	{
		cli.getWManager().newEntities(new Shoot(this->name, this->pos.x+34,this->pos.y, 1));
		cli.getWManager().newEntities(new Shoot(this->name, this->pos.x+34,this->pos.y, 0));
		cli.getWManager().newEntities(new Shoot(this->name, this->pos.x+34,this->pos.y, 2));
		this->power_up++;
		this->lim_fire = 50;
		if (this->power_up == 10)
			this->power_up = 0;
	}

}

void	Player::playEvent(Plat& cli)
{
	const sf::Input& i = cli.mainGui.GetInput();
	this->state = 2;
	if (this->lim_fire > 0)
	this->lim_fire--;
	for (std::map<int,PtrInput>::iterator it = PtrMeth.begin(); it != PtrMeth.end(); it++)
	{
		if (i.IsKeyDown((sf::Key::Code)it->first))
		{
			PtrInput ptr = it->second;
			(this->*ptr)(cli);
		}
	}
	this->Move();
}

sf::Drawable*	Player::getEntities()
{
	return &this->sprite;
}

void	Player::getState()
{
	if (this->state == 1)
		this->state = 4;
	if (this->state == -1)
		this->state = 0;
}

void	Player::Move()
{
	this->getState();
	this->sprite.SetSubRect(sf::IntRect(this->state * 33, 1 * 17,(this->state + 1) * 33, (1 + 1) * 17));
	this->sprite.SetX(this->pos.x);
	this->sprite.SetY(this->pos.y);
}

sf::Sprite Player::getSprite()
{
	return this->sprite;
}


float Player::getPosX()
{
	return this->pos.x;
}

float Player::getPosY()
{
	return this->pos.y;
}

int	Player::getLife()
{
	return this->life;
}

void	Player::setLife(int _life)
{
	this->life = _life;
}

int		Player::getIdT()
{
	return this->id_t;
}

int		Player::getIdMob()
{
	return 0;
}

std::string		Player::getPlayName()
{
	return "";
}

void		Player::setPos(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
}