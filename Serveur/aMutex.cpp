#include "aMutex.h"

aMutex::aMutex()
{
	#ifndef	_WIN32
		pthread_mutex_init(&(this->_mutex), NULL);
	#else
		InitializeCriticalSection(&(this->_mutex));
	#endif
}

aMutex::~aMutex()
{
	#ifndef _WIN32
		pthread_mutex_destroy(&(this->_mutex));
	#else
		DeleteCriticalSection(&(this->_mutex));
	#endif
}

void	aMutex::Lock()
{
	#ifndef _WIN32
		pthread_mutex_lock(&(this->_mutex));
	#else
		EnterCriticalSection(&(this->_mutex));
	#endif
}

int	aMutex::TryLock()
{
	#ifndef _WIN32
		return pthread_mutex_trylock(&(this->_mutex));
	#else
		return TryEnterCriticalSection(&(this->_mutex));
	#endif
}

void	aMutex::UnLock()
{
	#ifndef _WIN32
		pthread_mutex_unlock(&(this->_mutex));
	#else
		LeaveCriticalSection(&(this->_mutex));
	#endif
}
