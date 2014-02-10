#include "Server.h"
#include "iBlast.h"

Server::Server(const int& port)
{
	_Datas = new DataManager< Packet >;
	_SocketNFO = new SockServer(port);
	_TasksManager = new ThreadPool(*_Datas, *_SocketNFO);
}

Server::~Server()
{
	delete _Datas;
	delete _SocketNFO;
	delete _TasksManager;
}

void	Server::Looper()
{
	while (1)
	{
		Packet	packet;
		this->_SocketNFO->RecvFrom(packet._packet, &packet._fromPlayer, sizeof(packet._fromPlayer));
		this->_Datas->catchReceiver();
		this->_Datas->getReceiver().push_back(packet);
		this->_Datas->freeReceiver();
	}
}

void	Server::RunNetwork()
{
	this->_SocketNFO->Open();
	this->_SocketNFO->Bind();
	this->_TasksManager->LaunchPool();
	this->Looper();
}
