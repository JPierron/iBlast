#include "GuiMenu.h"

MenuWidget::MenuWidget(const std::string& file, const float& x, const float& y)
{
	_x = x;
	_y = y;
	_image.LoadFromFile(file);
	_sprite.SetImage(_image);
	_sprite.SetX(x);
	_sprite.SetY(y);
}

GuiMenu::GuiMenu(Gui& mainGui) : MainGui(mainGui)
{
	this->BackGround = new MenuWidget("Ressources/BackGround.jpg", 0, 0);
	this->BtnSolo = new MenuWidget("Ressources/BtnSolo.png", 550, 250);
	this->BtnMulti = new MenuWidget("Ressources/BtnMulti.png", 550, 300);
	this->BtnQuit = new MenuWidget("Ressources/BtnQuit.png", 550, 350);
}

void	GuiMenu::DrawMenu()
{
	this->MainGui.Draw(this->BackGround->_sprite);
	this->MainGui.Draw(this->BtnSolo->_sprite);
	this->MainGui.Draw(this->BtnMulti->_sprite);
	this->MainGui.Draw(this->BtnQuit->_sprite);
}
