#include "Plat.h"

Plat::Plat(Gui& _mainGui) : mainGui(_mainGui)
{
	WManager = new EntitiesManager();
	name = mainGui.IBlast._Pseudo;
	life = 5;
	pts = 0;
	hud = new InfoPlayer(name, life, pts); // declaration de l'objet
	mainGui.IBlast.gDatas().catchClients();
	if (mainGui.IBlast.gDatas().getClients()[mainGui.IBlast._Pseudo] == true)
	{
		Colision	*Traitor = new Colision(WManager->getSEntities(), mainGui.IBlast);
		ThdCol = new aThread();
		ThdCol->Create(&Colision::LaunchCheck, Traitor);
	}
	mainGui.IBlast.gDatas().freeClients();
}

Plat::~Plat()
{
}

void	Plat::sendSprite()
{
}

void	Plat::recvSprite()
{

}

const std::string&	Plat::getName()
{
	return this->name;
}

void	Plat::SendMySprite()
{
	std::list<Entities*>::iterator it = this->WManager->getSEntities().GetData().begin();

	for (; it != this->WManager->getSEntities().GetData().end(); it++)
	{
		if ((*it)->getName().compare(this->name) == 0)
		{
			Serializer<IBLAST::PackPosHero> ser;
			ser.GData()._type = IBLAST::_POS_HERO;
			ser.GData()._life = (*it)->getLife();
			ser.GData()._weapon = 0;
			ser.GData()._x = (*it)->getPosX();
			ser.GData()._y = (*it)->getPosY();
			memset(ser.GData()._playerName, '\0', IBLAST::_MAX_NAME_LEN);
			memcpy(ser.GData()._playerName, (*it)->getName().c_str(), IBLAST::_MAX_NAME_LEN);
			ser.Serialize();
			if (this->tmp_x != (*it)->getPosX() || this->tmp_y != (*it)->getPosY())
			{
				this->tmp_x = (*it)->getPosX();
				this->tmp_y = (*it)->getPosY();
				this->mainGui.IBlast.gSocketNFO().SendTo(ser.GBinData());
			}
		}
		if ((*it)->getType() == SHOT && (*it)->getPlayName().compare(this->name) == 0)
		{
			Serializer<IBLAST::PackPosShot> ser;
			ser.GData()._type = IBLAST::_POS_SHOT;
			ser.GData()._id = (*it)->getIdT();
			ser.GData()._x = (int)(*it)->getPosX();
			ser.GData()._y = (int)(*it)->getPosY();
			memset(ser.GData()._playerName, '\0', IBLAST::_MAX_NAME_LEN);
			memcpy(ser.GData()._playerName, (*it)->getPlayName().c_str(), IBLAST::_MAX_NAME_LEN);
			ser.Serialize();
			this->mainGui.IBlast.gSocketNFO().SendTo(ser.GBinData());
		}
	}
}

void	Plat::Start()
{
	std::list<sf::Drawable*>::iterator it;

	mainGui.Display();
	this->WManager->initBG();	
	this->WManager->newEntities(new Player(name,400,400));
	while (mainGui.IsOpened())
	{
		mainGui.GetEvent(this->e); 
		this->getWManager().catchEntities();
		this->WManager->playEvent(*this);
		this->sprites = this->WManager->getAllEntities();
		this->getWManager().freeEntities();
		mainGui.Clear();
		for (it = this->sprites.begin(); it != this->sprites.end(); it++)
			mainGui.Draw(*(*it));
		this->getWManager().catchEntities();
		this->SendMySprite();
		this->getWManager().freeEntities();
		this->hud->playHUD(*this, this->mainGui);
		mainGui.Display(); 
	}
}

EntitiesManager&	Plat::getWManager()
{
	return (*this->WManager);
}

void		Plat::setLife(int _life)
{
	this->life = _life;
}

int		Plat::getLife()
{
	return this->life;
}

int		Plat::getPts()
{
	return this->pts;
}

void		Plat::setPts(int _pts)
{
	this->pts = _pts;
}
