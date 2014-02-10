#ifndef _THREADPOOL_
# define _THREADPOOL_

#include <iostream>
#include <list>
#include "aThread.h"
#include "Packet.hpp"
#include "DataManager.hpp"
#include "SockServer.h"

class	SockServer;

class								ThreadPool
{
	std::list< aThread* >			_traitors;
	DataManager< Packet >&	_datas;
	SockServer&						_socket;
public:
	ThreadPool(DataManager< Packet >& datas, SockServer& socket);
	~ThreadPool();
	void							LaunchPool(void);
};

#endif
