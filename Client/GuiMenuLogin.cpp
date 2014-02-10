#include "GuiMenuLogin.h"

MenuLoginWidget::MenuLoginWidget(const std::string& value, const std::string& file, const float& x, const float& y)
{
	_x = x;
	_y = y;
	_image.LoadFromFile(file);
	_sprite.SetImage(_image);
	_sprite.SetX(x);
	_sprite.SetY(y);
	_value.Pos = 0;
	_value.Text = value;
	UpdateText();
}

void	MenuLoginWidget::UpdateText()
{
	this->_value.Input.SetText(this->_value.Text);
	this->_value.Input.SetSize(18);
	this->_value.Input.SetPosition((this->_x + 5), (this->_y + 34));
	this->_value.Input.SetColor(sf::Color(0, 0, 0));
}

void	MenuLoginWidget::UpdateError()
{
	this->_value.Input.SetText(this->_value.Text);
	this->_value.Input.SetSize(15);
	this->_value.Input.SetPosition((this->_x + 15), (this->_y + 43));
	this->_value.Input.SetColor(sf::Color(255, 50, 50));
}

GuiMenuLogin::GuiMenuLogin(Gui& mainGui) : MainGui(mainGui)
{
	BackGround = new MenuWidget("Ressources/BackGround.jpg", 0, 0);
	Inputs.insert(std::pair< int, MenuLoginWidget* >(ADDRESS, new MenuLoginWidget("192.168.88.1", "Ressources/InputAddress.png", 400, 150)));
	Inputs.insert(std::pair< int, MenuLoginWidget* >(PORT, new MenuLoginWidget("3400", "Ressources/InputPort.png", 400, 225)));
	Inputs.insert(std::pair< int, MenuLoginWidget* >(PSEUDO, new MenuLoginWidget("Jean", "Ressources/InputPseudo.png", 400, 300)));
	Error = new MenuLoginWidget("", "Ressources/Error.png", 300, 500);
	BtnLogin = new MenuWidget("Ressources/BtnConnect.png", 400, 375);
	BtnQuit = new MenuWidget("Ressources/BtnQuit.png", 600, 25);
	InputSelected = ADDRESS;
	isError = false;
}

void	GuiMenuLogin::DrawMenuLogin()
{
	this->MainGui.Draw(this->BackGround->_sprite);
	this->MainGui.Draw(this->BtnLogin->_sprite);
	this->MainGui.Draw(this->BtnQuit->_sprite);
	this->MainGui.Draw(this->Inputs[ADDRESS]->_sprite);
	this->MainGui.Draw(this->Inputs[PORT]->_sprite);
	this->MainGui.Draw(this->Inputs[PSEUDO]->_sprite);
	if (this->isError)
	{
		this->MainGui.Draw(this->Error->_sprite);
		this->MainGui.Draw(this->Error->_value.Input);
		this->isError = false;
	}
	this->MainGui.Draw(this->Inputs[ADDRESS]->_value.Input);
	this->MainGui.Draw(this->Inputs[PORT]->_value.Input);
	this->MainGui.Draw(this->Inputs[PSEUDO]->_value.Input);
}
