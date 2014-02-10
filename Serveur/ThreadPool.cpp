#include "ThreadPool.h"
#include "Routine.h"
#include "iBlast.h"

class	SockServer;

ThreadPool::ThreadPool(DataManager< Packet >& datas, SockServer& socket) : _datas(datas), _socket(socket)
{
	for (int i = 0; i < IBLAST::_MAX_TH; i++)
		_traitors.push_back(new aThread);
}

ThreadPool::~ThreadPool()
{
	std::list< aThread* >::iterator it = _traitors.begin();
	for (; it != _traitors.end(); it++)
		delete (*it);
}

void			ThreadPool::LaunchPool()
{
	std::list< aThread* >::iterator it = _traitors.begin();
	for (int i = 1; it != _traitors.end(); it++, i++)
	{
		Routines	*Traitor = new Routines(*this, this->_datas, this->_socket);
		(*it)->Create(&Routines::LaunchRoutine, Traitor);
	}
}
