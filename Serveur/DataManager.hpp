#ifndef _DATA_MANAGER_
# define _DATA_MANAGER_

#include <iostream>
#include <string>
#include <map>
#include <list>
#include "aMutex.h"
#include "ThreadSafeData.hpp"

template	< class DataR >
class														DataManager
{
	ThreadSafeData< std::list< DataR > >					_Receiver;
	ThreadSafeData< std::map< std::string, sockaddr_in > >	_Clients;
	ThreadSafeData< std::string >							_Master;
	ThreadSafeData< bool >									_Launched;
public:
	DataManager()
	{
		_Launched.CatchData();
		_Launched.GetData() = false;
		_Launched.FreeData();
		_Master.CatchData();
		_Master.GetData() = "";
		_Master.FreeData();
		_Receiver.CatchData();
		_Receiver.FreeData();
		_Clients.CatchData();
		_Clients.FreeData();
	}
	~DataManager(){}
	void													catchReceiver()
	{
		return this->_Receiver.CatchData();
	}
	void													catchClients()
	{
		return this->_Clients.CatchData();
	}
	void													catchLaunched()
	{
		return this->_Launched.CatchData();
	}
	void													catchMaster()
	{
		return this->_Master.CatchData();
	}
	std::list< DataR >&										getReceiver()
	{
		return this->_Receiver.GetData();
	}
	std::map< std::string, sockaddr_in >&					getClients()
	{
		return this->_Clients.GetData();
	}
	bool&													getLaunched()
	{
		return this->_Launched.GetData();
	}
	std::string&											getMaster()
	{
		return this->_Master.GetData();
	}
	void													freeReceiver()
	{
		this->_Receiver.FreeData();
	}
	void													freeClients()
	{
		this->_Clients.FreeData();
	}
	void													freeMaster()
	{
		this->_Master.FreeData();
	}
	void													freeLaunched()
	{
		this->_Launched.FreeData();
	}
};

#endif
