#ifndef _ENTITIESMANAGER_
#define _ENTITIESMANAGER_
#include "Entities.h"
#include <list>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Plat.h"
#include "Player.h"
#include "iBlast.h"
#include "Colision.h"
#include "ThreadSafeData.hpp"

class Plat;
class Colision;
class Entities;
class EntitiesManager
{
	ThreadSafeData< std::list<Entities*> >	entities;
	Colision				*col;
public:
	EntitiesManager();
	~EntitiesManager();
	void						newEntities(Entities*);
	void						playEvent(Plat&);
	void						initBG();
	void						catchEntities();
	void						freeEntities();
	std::list<Entities*>&		getEntities();
	ThreadSafeData< std::list<Entities*> >&	getSEntities();
	std::list<sf::Drawable*>	getAllEntities();
};


#endif