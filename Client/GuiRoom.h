#ifndef _GUI_ROOM_
# define _GUI_ROOM_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "GuiMenu.h"
#include "GuiMenuLogin.h"
#include "Gui.h"

struct	OutputPseudo
{
	sf::String	Input;
	std::string	Text;
};

struct				RoomPlayerWidget
{
	float			_x;
	float			_y;
	sf::Image		_image;
	sf::Sprite		_sprite;
	OutputPseudo	_player;
	RoomPlayerWidget(const std::string& name, const std::string& file, const float& x, const float& y);
	void			UpdateText(const int& i);
};

struct								RoomWidget
{
	float							_x;
	float							_y;
	sf::Image						_imageS;
	sf::Image						_imageM;
	sf::Sprite						_sprite;
	std::list< RoomPlayerWidget* >	_players;
	RoomWidget(const float& x, const float& y);
	void							UpdateList(std::map< std::string, bool >& players);
};

struct	MenuWidget;
class	Gui;
class					GuiRoom
{
	MenuWidget*			BackGround;
	MenuWidget*			BtnQuit;
public:
	RoomWidget*			ListPlayer;
	Gui&				MainGui;
	GuiRoom(Gui& mainGui);
	void				DrawRoom();
};

#endif
