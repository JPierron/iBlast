#include "EntitiesManager.h"

EntitiesManager::EntitiesManager()
{
	this->catchEntities();
	this->freeEntities();
}

EntitiesManager::~EntitiesManager()
{
}


void	EntitiesManager::newEntities(Entities* wid)
{
	this->entities.GetData().push_back(wid);
}

void	EntitiesManager::playEvent(Plat& cli)
{
	std::list<Entities*>::iterator it = this->entities.GetData().begin();


	for(; it!= this->entities.GetData().end(); it++)
	{
 		(*it)->sTMPx((*it)->getPosX());
		(*it)->sTMPy((*it)->getPosY());
		(*it)->playEvent(cli);
		if ((*it)->getType() != IBLAST::_POS_HERO && (*it)->getTMPx() == (*it)->getPosX() && (*it)->getTMPy() == (*it)->getPosY())
		{
			(*it)->ok++;
			if ((*it)->ok == 100)
			{
				delete (*it);
				this->entities.GetData().erase(it);
				it = this->entities.GetData().begin();
				(*it)->ok = 0;
			}	
		}
		else
		{
			(*it)->ok = 0;
		}
		if ((((*it)->getType() == IBLAST::_POS_SHOT_MOB || (*it)->getType() == IBLAST::_POS_ENN_I)  && (*it)->getPosX() < 0 ) ||
			((*it)->getType() == IBLAST::_POS_SHOT_MOB  && ((*it)->getPosY() < 0 || (*it)->getPosY() > (600-IBLAST::BLIFE))) || 
			((*it)->getType() == IBLAST::_POS_SHOT && (*it)->getPosX() > 850) || ((*it)->getType() == EXPLOSION && (*it)->getLife() == 1))
		{
			delete (*it);
			this->entities.GetData().erase(it);
			it = this->entities.GetData().begin();
		}
	}	
}

void	EntitiesManager::catchEntities()
{
	this->entities.CatchData();
}

std::list<Entities*>&	EntitiesManager::getEntities()
{
	return this->entities.GetData();
}

ThreadSafeData<std::list<Entities*>>&	EntitiesManager::getSEntities()
{
	return this->entities;
}

void	EntitiesManager::freeEntities()
{
	this->entities.FreeData();
}

std::list<sf::Drawable*>	EntitiesManager::getAllEntities()
{
	std::list<Entities*>::iterator it = this->entities.GetData().begin();
	std::list<sf::Drawable*> listd;

	for(; it!= this->entities.GetData().end(); it++)
		listd.push_back((*it)->getEntities());
	return (listd);
}

void	EntitiesManager::initBG()
{
	this->newEntities(new DefBack(0,0));
	this->newEntities(new DefBack(800,0));	
}