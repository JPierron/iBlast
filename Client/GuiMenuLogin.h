#ifndef _GUI_MENU_LOGIN_
# define _GUI_MENU_LOGIN_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "GuiMenu.h"
#include "Gui.h"

enum INPUTS { ADDRESS = 1, PORT = 2, PSEUDO = 3 };

struct			InputText
{
	sf::String	Input;
	std::string	Text;
	int			Pos;
};

struct			MenuLoginWidget
{
	float		_x;
	float		_y;
	sf::Image	_image;
	sf::Sprite	_sprite;
	InputText	_value;
	MenuLoginWidget(const std::string& value, const std::string& name, const float& x, const float& y);
	void		UpdateText();
	void		UpdateError();
};

struct	MenuWidget;
class	Gui;
class									GuiMenuLogin
{
	MenuWidget*							BackGround;
	MenuWidget*							BtnQuit;
	MenuWidget*							BtnLogin;
public:
	bool								isError;
	MenuLoginWidget*					Error;
	std::map< int , MenuLoginWidget* >	Inputs;
	int									InputSelected;
	Gui&								MainGui;
	GuiMenuLogin(Gui& mainGui);
	void								DrawMenuLogin();
};

#endif
