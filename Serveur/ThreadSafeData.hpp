#ifndef _THREAD_SAFE_DATA_
# define _THREAD_SAFE_DATA_

#include "aMutex.h"

///////////////////////////////////////////////////////////////////////
// Classe template heritant de l'abstraction mutex,
//	Protege les donnees _Data lors des echanges entre threads
//	Chaque _Data < de type T > serra lier a un verrou

template <class T>
class		ThreadSafeData : public aMutex
{
	T		_Data;
public:
	ThreadSafeData() : aMutex()
	{}
	~ThreadSafeData()
	{}
	void	CatchData()
	{
		this->Lock();
	}
	T&	GetData()
	{
		return this->_Data;
	}
	void	FreeData()
	{
		this->UnLock();
	}
};

#endif
