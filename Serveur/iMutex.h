#ifndef	_I_MUTEX_
# define _I_MUTEX_

class				iMutex
{
public:
	virtual void	Lock() = 0;
	virtual int		TryLock() = 0;
	virtual void	UnLock() = 0;
};

#endif
