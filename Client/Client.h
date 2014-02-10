#ifndef _SERVER_
# define _SERVER_

#include "iNetwork.h"
#include "Packet.hpp"
#include "SockClient.h"
#include "ThreadPool.h"
#include "Gui.h"
#include "DataManager.hpp"

class	Gui;
class	ThreadPool;
class	SockClient;
class								Client	:	public iNetwork
{
	Gui*							_Gui;
	DataManager< char* >*			_Datas;
	SockClient*						_SocketNFO;
	ThreadPool*						_TasksManager;
public:
	ThreadSafeData< bool >			_Actualizer;
	std::string						_Pseudo;
	bool							_Looper;
	Client(const std::string& adress, const int& port = 3400);
	~Client();
	DataManager< char* >&			gDatas();
	SockClient&						gSocketNFO();
	ThreadPool&						gTasksManager();
	Gui&							gGui();
	void							RunIBlast();
	void							RunNetwork();
};

#endif
