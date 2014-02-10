#ifndef _SERVER_
# define _SERVER_

#include "iNetwork.h"
#include "Packet.hpp"
#include "SockServer.h"
#include "ThreadPool.h"
#include "DataManager.hpp"

class								Server	:	public iNetwork
{
	DataManager< Packet >*			_Datas;
	SockServer*						_SocketNFO;
	ThreadPool*						_TasksManager;
public:
	Server(const int& port = 3400);
	~Server();
	void							Looper();
	void							RunNetwork();
};

#endif
