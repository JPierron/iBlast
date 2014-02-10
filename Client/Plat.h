#ifndef _PLAT_
#define _PLAT_
#include <stdlib.h>
#include <list>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "iBlast.h"
#include "EntitiesManager.h"
#include "Player.h"
#include "DefBackground.h"
#include "Pepel.h"
#include "MazzelTof.h"
#include "InfoPlayer.h"
#include "Gui.h"
#include "aThread.h"
#include "Colision.h"

class EntitiesManager;
class Player;
class InfoPlayer;
class Gui;
class	Plat
{
	EntitiesManager*			WManager;
	std::list<sf::Drawable*>	sprites;
	sf::Event					e;
	std::string					name;
	int							life;
	aThread*					ThdCol;
	bool						master;
    InfoPlayer*                 hud;
	int							pts;
	float						tmp_x;
	float						tmp_y;
public:
	Gui&				mainGui;
	Plat(Gui& mainGui);
	~Plat();
	EntitiesManager&	getWManager();
	void				sendSprite();
	void				recvSprite();
	char*		createPacket(char*);
	void				Start();	
	const std::string&	getName();
	void				setPts(int _pts);
	int					getPts();
	void				setLife(int _life);
	void				SendMySprite();
	int					getLife();
};

#endif