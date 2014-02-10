#ifndef _GUI_
# define _GUI_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <map>
#include "Client.h"
#include "GuiMenu.h"
#include "GuiRoom.h"
#include "GuiMenuLogin.h"
#include "Plat.h"

enum GUIS { MENU = 1, MENU_LOGIN = 2, ROOM = 3, GAME = 4 };

class				Gui;
typedef	void	(Gui::*Events)(const sf::Event& _event);

class	Client;
class	GuiMenu;
class	GuiRoom;
class	GuiMenuLogin;
class						Gui : public sf::RenderWindow
{
	sf::Event				Event;
	std::map< int, Events >	EventsTasker;
	bool					Launched;
public:
	bool					Multi;
	int						CurrentWindow;
	GuiMenu*				Menu;
	GuiRoom*				Room;
	Plat*					Game;
	GuiMenuLogin*			MenuLogin;
	Client&					IBlast;
	Gui(Client& rType, const std::string& name);
	void					Run();
	void					MenuEvents(const sf::Event& _event);
	void					MenuLoginEvents(const sf::Event& _event);
	void					RoomEvents(const sf::Event& _event);
	bool					Connection();
};

#endif
