#include "GuiRoom.h"

RoomWidget::RoomWidget(const float& x, const float& y)
{
	_x = x;
	_y = y;
	_imageS.LoadFromFile("Ressources/RoomSlave.png");
	_imageM.LoadFromFile("Ressources/RoomMaster.png");
	_sprite.SetX(x);
	_sprite.SetY(y);
	_players.clear();
}

RoomPlayerWidget::RoomPlayerWidget(const std::string& name, const std::string& file, const float& x, const float& y)
{
	_x = x;
	_y = y;
	_image.LoadFromFile(file);
	_sprite.SetImage(_image);
	_sprite.SetX(x);
	_sprite.SetY(y);
	_player.Text = name;
}

void	RoomWidget::UpdateList(std::map< std::string, bool >& players)
{
	std::list< RoomPlayerWidget* >::iterator player;
	while (!this->_players.empty())
	{
		player = this->_players.begin();
		delete (*player);
		this->_players.erase(player);
	}
	std::map< std::string, bool >::iterator playerWid= players.begin();
	for (int i = 0; playerWid != players.end(); playerWid++, i++)
	{
		switch (i)
		{
		case 0:
			this->_players.push_back(new RoomPlayerWidget((*playerWid).first, "Ressources/Master.jpg", 410, 185));
			this->_players.back()->UpdateText(i);
			break;
		case 1:
			this->_players.push_back(new RoomPlayerWidget((*playerWid).first, "Ressources/Slave.jpg", 410, 230));
			this->_players.back()->UpdateText(i);
			break;
		case 2:
			this->_players.push_back(new RoomPlayerWidget((*playerWid).first, "Ressources/Slave.jpg", 410, 275));
			this->_players.back()->UpdateText(i);
			break;
		case 3:
			this->_players.push_back(new RoomPlayerWidget((*playerWid).first, "Ressources/Slave.jpg", 410, 320));
			this->_players.back()->UpdateText(i);
			break;
		}
	}
}

void	RoomPlayerWidget::UpdateText(const int& i)
{
	this->_player.Input.SetText(this->_player.Text);
	this->_player.Input.SetSize(18);
	this->_player.Input.SetPosition((this->_x + 38), (this->_y + 8));
	switch (i)
	{
	case 0:
		this->_player.Input.SetColor(sf::Color(255, 132, 107)); break;
	case 1:
		this->_player.Input.SetColor(sf::Color(82, 115, 255)); break;
	case 2:
		this->_player.Input.SetColor(sf::Color(123, 255, 123)); break;
	case 3:
		this->_player.Input.SetColor(sf::Color(255, 148, 155)); break;
	}
}

GuiRoom::GuiRoom(Gui& mainGui) : MainGui(mainGui)
{
	this->BackGround = new MenuWidget("Ressources/BackGround.jpg", 0, 0);
	this->ListPlayer = new RoomWidget(400, 175);
	this->BtnQuit = new MenuWidget("Ressources/BtnQuit.png", 600, 25);
}

void	GuiRoom::DrawRoom()
{
	this->MainGui.Draw(this->BackGround->_sprite);
	this->MainGui.Draw(this->BtnQuit->_sprite);
	this->MainGui.IBlast.gDatas().catchClients();
	if (this->MainGui.IBlast.gDatas().getClients()[this->MainGui.IBlast._Pseudo] != false)
		this->MainGui.Room->ListPlayer->_sprite.SetImage(this->MainGui.Room->ListPlayer->_imageM);
	else
		this->MainGui.Room->ListPlayer->_sprite.SetImage(this->MainGui.Room->ListPlayer->_imageS);
	this->MainGui.IBlast.gDatas().freeClients();
	this->MainGui.Draw(this->ListPlayer->_sprite);
	std::list< RoomPlayerWidget* >::iterator it = this->ListPlayer->_players.begin();
	for (; it != this->ListPlayer->_players.end(); it++)
	{
		this->MainGui.Draw(((*it)->_sprite));
		this->MainGui.Draw((*it)->_player.Input);
	}
}
