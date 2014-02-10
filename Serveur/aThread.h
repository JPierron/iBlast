#ifndef _A_THREAD_
# define _A_THREAD_

#include <iostream>
#include "iThread.h"

#ifndef _WIN32
	#include <pthread.h>
	#include <signal.h>
	typedef pthread_t	Handle;
#else
	#include <windows.h>
	typedef HANDLE		Handle;
#endif

class		aThread : public iThread
{
	Handle	_handle;
public:
	aThread();
	~aThread();
	bool	Create(void* routine, void* args);
	void	Join();
	void	Kill();
};

#endif
