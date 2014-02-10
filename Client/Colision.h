#ifndef _COLISION_
#define _COLISION_
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Plat.h"
#include "Client.h"
#include "Explosion.h"
#include "ThreadSafeData.hpp"
#include "Serializer.hpp"
#include "iBlast.h"
class Colision;
typedef bool (Colision::*PtrCol)(Entities&, Entities&);


class Client;
class Explosion;
template <class T>
class Serializer;
class Colision
{
	int										state;
	int										tuile;
	std::map<int,PtrCol>					PtrMeth;
	ThreadSafeData< std::list<Entities*> >&	SEnts;
	Client&									IBlast;
public:
	Colision(ThreadSafeData< std::list<Entities*> >&, Client&);
	~Colision();
	bool		doMobHero(Entities&, Entities&);
	bool		doShootMob(Entities&, Entities&);
	bool		doHeroShot(Entities&, Entities&);
	char*		createPacket(char*);
	void		AddEntByTuile();
	void		SendPosMob();
	static int	LaunchCheck(void*);
	void		StartCheck();
	sf::IntRect	Colision::getIntRect(const sf::Sprite&);
	int			getState();
};

#endif