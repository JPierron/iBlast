#include "aThread.h"

aThread::aThread()
{
	_handle = NULL;
}

aThread::~aThread()
{
}

bool	aThread::Create(void* routine, void* args)
{
	#ifndef _WIN32
		if (this->_handle == 0)
			if (pthread_create(&(this->_handle), NULL, (void*(*)(void*)) routine, args) != 0)
			{
				std::cerr << "Problem on Thread creation" << std::endl;
				return false;
			}
	#else
		if (this->_handle == NULL)
			if ((this->_handle = CreateThread(NULL, 0, static_cast<LPTHREAD_START_ROUTINE>(routine), args, 0, NULL)) == NULL)
			{
				std::cerr << "Problem on Thread creation" << std::endl;
				return false;
			}
	#endif
	return true;
}

void	aThread::Join()
{
	#ifndef _WIN32
		if (this->_handle != 0 && pthread_join(this->_handle, NULL) != 0)
			std::cerr << "Problem pthread_kill" << std::endl;
	#else
		if (this->_handle != NULL)
			WaitForSingleObject(this->_handle, INFINITE);
	#endif
}

void	aThread::Kill()
{
	#ifndef _WIN32
		if (this->_handle != 0 && pthread_kill(this->_handle, SIGSTOP) != 0)
			std::cerr << "Problem pthread_kill" << std::endl;
		else
			this->_handle = NULL;
	#else
		if (this->_handle != NULL)
		{
			TerminateThread(this->_handle, 0);
			this->_handle = NULL;
		}
	#endif
}
