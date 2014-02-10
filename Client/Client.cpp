#include "Client.h"
#include "iBlast.h"

Client::Client(const std::string& address, const int& port)
{
	_Actualizer.GetData() = false;
	_Datas = new DataManager< char* >;
	_SocketNFO = new SockClient;
	_TasksManager = new ThreadPool(*this);
	_Gui = new Gui(*this, "iBlast");
	_Looper = false;
}

Client::~Client()
{
	delete _Datas;
	delete _Gui;
	delete _SocketNFO;
	delete _TasksManager;
}

DataManager< char* >&	Client::gDatas()
{
	return *this->_Datas;
}

SockClient&	Client::gSocketNFO()
{
	return *this->_SocketNFO;
}

ThreadPool&	Client::gTasksManager()
{
	return *this->_TasksManager;
}

Gui&	Client::gGui()
{
	return *this->_Gui;
}

void	Client::RunIBlast()
{
	this->_Gui->Run();
}

void	Client::RunNetwork()
{
	this->_TasksManager->LaunchPool();
}
