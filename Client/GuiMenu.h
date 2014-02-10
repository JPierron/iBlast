#ifndef _GUI_MENU_
# define _GUI_MENU_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "Gui.h"

struct			MenuWidget
{
	float		_x;
	float		_y;
	sf::Image	_image;
	sf::Sprite	_sprite;
	MenuWidget(const std::string& name, const float& x, const float& y);
};

class Gui;
class			GuiMenu
{
	MenuWidget*	BackGround;
	MenuWidget*	BtnSolo;
	MenuWidget*	BtnMulti;
	MenuWidget*	BtnQuit;
public:
	Gui&		MainGui;
	GuiMenu(Gui& mainGui);
	void		DrawMenu();
};

#endif
