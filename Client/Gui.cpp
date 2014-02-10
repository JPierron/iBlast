#include "Gui.h"
#include "iBlast.h"
#include "Packet.hpp"
#include "Serializer.hpp"

Gui::Gui(Client& iBlast, const std::string& name) : sf::RenderWindow(sf::VideoMode(800, 600, 32), name), IBlast(iBlast)
{
	SetFramerateLimit(60);
	Menu = new GuiMenu(*this);
	Room = new GuiRoom(*this);
	Game = NULL;
	MenuLogin = new GuiMenuLogin(*this);
	CurrentWindow = MENU;
	Launched = true;
	Multi = false;
	EventsTasker.insert(std::pair< int, Events >(MENU, &Gui::MenuEvents));
	EventsTasker.insert(std::pair< int, Events >(MENU_LOGIN, &Gui::MenuLoginEvents));
	EventsTasker.insert(std::pair< int, Events >(ROOM, &Gui::RoomEvents));
}

void	Gui::Run()
{
	this->Menu->DrawMenu();
	this->Display();
	while (this->Launched != false)
	{
		switch (this->CurrentWindow)
		{
		case MENU:
			this->Menu->DrawMenu(); break;
		case MENU_LOGIN:
			this->MenuLogin->DrawMenuLogin(); break;
		case ROOM:
			{
				this->IBlast.gDatas().catchClients();
				this->Room->ListPlayer->UpdateList(this->IBlast.gDatas().getClients());
				this->IBlast.gDatas().freeClients();
				this->Room->DrawRoom();
			} break;
		case GAME:
			{
				if (this->Game == NULL)
				{
					this->IBlast.gGui().Game = new Plat(this->IBlast.gGui());
					this->IBlast.gGui().Game->Start();
				}
			}
		}
		this->Display();
		while (this->GetEvent(this->Event))
			if (this->CurrentWindow != GAME)
				(this->*EventsTasker[this->CurrentWindow])(this->Event);
	}
}

void	Gui::MenuEvents(const sf::Event &_event)
{
	switch (_event.Type)
	{
	case sf::Event::MouseButtonPressed:
		{
			int x = this->GetInput().GetMouseX();
			int y = this->GetInput().GetMouseY();
			if (x > 550 && x < 711 && y > 250 && y < 282)
			{
				this->Clear();
				this->CurrentWindow = GAME;
				this->IBlast.gDatas().getClients().insert(std::pair< std::string, bool >(this->IBlast._Pseudo, true));
				this->Game = new Plat(*this);
				this->Game->Start();
				this->Display();
			}
			else if (x > 550 && x < 711 && y > 300 && y < 332)
			{
				this->Clear();
				this->CurrentWindow = MENU_LOGIN;
				this->MenuLogin->DrawMenuLogin();
				this->Display();
			}
			else if (x > 550 && x < 711 && y > 350 && y < 382)
				this->Launched = false;
		} break;
	}
}

bool	Gui::Connection()
{
	int	ServErr;
	Serializer< IBLAST::PackConnection >	Connection;
	Connection.GData()._type = IBLAST::_CONNECTION;
	memset(Connection.GData()._playerName, '\0', IBLAST::_MAX_NAME_LEN);
	memcpy(Connection.GData()._playerName, this->MenuLogin->Inputs[PSEUDO]->_value.Text.c_str(), IBLAST::_MAX_NAME_LEN);
	Connection.Serialize();
	this->IBlast.gSocketNFO().SetUp(atoi(this->MenuLogin->Inputs[PORT]->_value.Text.c_str()), this->MenuLogin->Inputs[ADDRESS]->_value.Text);
	this->IBlast.gSocketNFO().Open();
	this->IBlast.gSocketNFO().SendTo(Connection.GBinData());
	Serializer< IBLAST::PackOkKo >	OkKo;
	ServErr = this->IBlast.gSocketNFO().RecvFrom(OkKo.GBinData());
	OkKo.UnSerialize();
	if (ServErr != -1 && OkKo.GData()._ok != false)
	{
		this->IBlast.gDatas().catchClients();
		this->IBlast._Pseudo = Connection.GData()._playerName;
		this->IBlast.gDatas().getClients().insert(std::pair< std::string, bool >(this->IBlast._Pseudo, OkKo.GData()._master));
		this->IBlast.gDatas().freeClients();
		this->IBlast._Pseudo = this->MenuLogin->Inputs[PSEUDO]->_value.Text;
		return true;
	}
	else if (ServErr != -1)
	{
		this->MenuLogin->Error->_value.Text = OkKo.GData()._mess;
		this->MenuLogin->Error->UpdateError();
		this->IBlast.gSocketNFO().Close();
		return false;
	}
	else
	{
		this->MenuLogin->Error->_value.Text = "Le serveur n'est pas joignable.";
		this->MenuLogin->Error->UpdateError();
		this->IBlast.gSocketNFO().Close();
		return false;
	}
}

void	Gui::MenuLoginEvents(const sf::Event &_event)
{
	switch (_event.Type)
	{
	case sf::Event::MouseButtonPressed:
		{
			int x = this->GetInput().GetMouseX();
			int y = this->GetInput().GetMouseY();
			if (x > 400 && x < 561 && y > 375 && y < 408)
			{
				if (this->Connection())
				{
					this->Multi = true;
					this->CurrentWindow = ROOM;
					this->IBlast.gDatas().catchClients();
					this->Room->ListPlayer->UpdateList(this->IBlast.gDatas().getClients());
					this->IBlast.gDatas().freeClients();
					this->IBlast.RunNetwork();
					this->Room->DrawRoom();
				}
				else
				{
					this->MenuLogin->isError = true;
					this->MenuLogin->DrawMenuLogin();
				}
				this->Display();
			}
			else if (x > 400 && x < 761 && y > 25 && y < 57)
			{
				this->Multi = false;
				this->CurrentWindow = MENU;
				this->Menu->DrawMenu();
				this->Display();
			}
			else if (x > 400 && x < 723 && y > 182 && y < 218)
				this->MenuLogin->InputSelected = ADDRESS;
			else if (x > 400 && x < 723 && y > 258 && y < 294)
				this->MenuLogin->InputSelected = PORT;
			else if (x > 400 && x < 723 && y > 332 && y < 368)
				this->MenuLogin->InputSelected = PSEUDO;
		} break;
	case sf::Event::TextEntered:
		{
			bool	noAction = false;
			if (_event.Text.Unicode == 8)
				this->MenuLogin->Inputs[this->MenuLogin->InputSelected]->_value.Text = this->MenuLogin->Inputs[this->MenuLogin->InputSelected]->_value.Text.substr(0, this->MenuLogin->Inputs[this->MenuLogin->InputSelected]->_value.Text.length() - 1);
			else if (this->MenuLogin->InputSelected == ADDRESS && (_event.Text.Unicode == 46 || _event.Text.Unicode >= 48 && _event.Text.Unicode <= 57) && this->MenuLogin->Inputs[this->MenuLogin->InputSelected]->_value.Text.length() < 15)
				this->MenuLogin->Inputs[this->MenuLogin->InputSelected]->_value.Text += (char)_event.Text.Unicode;
			else if (this->MenuLogin->InputSelected == PORT && (_event.Text.Unicode >= 48 && _event.Text.Unicode <= 57) && this->MenuLogin->Inputs[this->MenuLogin->InputSelected]->_value.Text.length() < 5)
				this->MenuLogin->Inputs[this->MenuLogin->InputSelected]->_value.Text += (char)_event.Text.Unicode;
			else if (this->MenuLogin->InputSelected == PSEUDO && ((_event.Text.Unicode >= 65 && _event.Text.Unicode <= 90) || (_event.Text.Unicode >= 97 && _event.Text.Unicode <= 122)) && this->MenuLogin->Inputs[this->MenuLogin->InputSelected]->_value.Text.length() < 16)
				this->MenuLogin->Inputs[this->MenuLogin->InputSelected]->_value.Text += (char)_event.Text.Unicode;
			else
				noAction = true;
			if (!noAction)
			{
				this->MenuLogin->Inputs[this->MenuLogin->InputSelected]->UpdateText();
				this->Clear();
				this->MenuLogin->DrawMenuLogin();
				this->Display();
			}
		} break;
	}
}

void	Gui::RoomEvents(const sf::Event &_event)
{
	switch (_event.Type)
	{
	case sf::Event::MouseButtonPressed:
		{
			int x = this->GetInput().GetMouseX();
			int y = this->GetInput().GetMouseY();
			if (x > 400 && x < 761 && y > 25 && y < 57)
			{
				while (!this->Room->ListPlayer->_players.empty())
				{
					delete this->Room->ListPlayer->_players.front();
					this->Room->ListPlayer->_players.pop_front();
				}
				Serializer< IBLAST::PackDisconnection >	Disconnection;
				Disconnection.GData()._type = IBLAST::_DISCONNECTION;
				memset(Disconnection.GData()._playerName, '\0', IBLAST::_MAX_NAME_LEN);
				memcpy(Disconnection.GData()._playerName, this->IBlast._Pseudo.c_str(), IBLAST::_MAX_NAME_LEN);
				Disconnection.Serialize();
				this->IBlast.gSocketNFO().SendTo(Disconnection.GBinData());
				this->IBlast.gSocketNFO().Close();
				this->IBlast.gDatas().catchClients();
				this->IBlast.gDatas().catchLaunched();
				this->IBlast.gDatas().catchMaster();
				this->IBlast.gDatas().catchReceiver();
				this->IBlast._Actualizer.CatchData();
				std::list< aThread* >::iterator it = this->IBlast.gTasksManager().gTraitors().begin();
				std::map< std::string, bool >::iterator cli;
				for (; it != this->IBlast.gTasksManager().gTraitors().end(); it++)
					(*it)->Kill();
				while (!this->IBlast.gDatas().getClients().empty())
				{
					cli = this->IBlast.gDatas().getClients().begin();
					this->IBlast.gDatas().getClients().erase(cli);
				}
				this->IBlast.gDatas().freeClients();
				this->IBlast.gDatas().freeLaunched();
				this->IBlast.gDatas().freeMaster();
				this->IBlast.gDatas().freeReceiver();
				this->IBlast._Actualizer.FreeData();
				this->CurrentWindow = MENU;
				this->Menu->DrawMenu();
				this->Display();
			}
			if (x > 400 && x < 723 && y > 545 && y < 577)
			{
				this->Clear();
				this->CurrentWindow = GAME;
				Serializer< IBLAST::PackLaunchGame >	launch;
				launch.GData()._type = IBLAST::_LAUNCH_GAME;
				memset(launch.GData()._playerName, '\0', IBLAST::_MAX_NAME_LEN);
				memcpy(launch.GData()._playerName, this->IBlast._Pseudo.c_str(), IBLAST::_MAX_NAME_LEN);
				launch.Serialize();
				this->IBlast.gSocketNFO().SendTo(launch.GBinData());
				this->Game = new Plat(*this);
				this->Game->Start();
				this->Display();
			}
		} break;
	}
}
