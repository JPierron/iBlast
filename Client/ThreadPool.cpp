#include "ThreadPool.h"
#include "Routine.h"
#include "iBlast.h"

ThreadPool::ThreadPool(Client& iblast) : _IBlast(iblast)
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
		Routines	*Traitor = new Routines(this->_IBlast);
		if (i == 1)
			(*it)->Create(&Routines::LaunchReceiver, Traitor);
		else
			(*it)->Create(&Routines::LaunchSender, Traitor);
	}
}

std::list< aThread* >&	ThreadPool::gTraitors()
{
	return this->_traitors;
}
