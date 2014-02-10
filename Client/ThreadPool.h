#ifndef _THREADPOOL_
# define _THREADPOOL_

#include <iostream>
#include <list>
#include "aThread.h"
#include "Packet.hpp"
//#include "DataManager.hpp"
//#include "SockClient.h"
#include "Client.h"

//class	SockClient;
class	Client;
class								ThreadPool
{
	std::list< aThread* >			_traitors;
	Client&							_IBlast;
public:
	ThreadPool(Client& rtype);
	~ThreadPool();
	std::list< aThread* >&			gTraitors();
	void							LaunchPool(void);
};

#endif
