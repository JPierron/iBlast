#ifndef	_A_MUTEX_
# define _A_MUTEX_

#include <iostream>
#include "iMutex.h"

#ifndef	_WIN32
	#include <pthread.h>
	typedef	pthread_mutex_t		Mutex;
#else
	#include <windows.h>
	typedef	CRITICAL_SECTION	Mutex;
#endif

class		aMutex : public iMutex
{
	Mutex	_mutex;
public:
	aMutex();
	~aMutex();
	void	Lock();
	int		TryLock();
	void	UnLock();
};

#endif
