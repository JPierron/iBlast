#ifndef _I_THREAD_
# define _I_THREAD_

class				iThread
{
public:
	virtual bool	Create(void* routine, void* args) = 0;
	virtual void	Join() = 0;
	virtual void	Kill() = 0;
};

#endif
