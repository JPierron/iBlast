#ifndef _I_SOCKET_UDP_
# define _I_SOCKET_UDP_

class	iSocketUDP
{
public:
	virtual void	Open() = 0;
	virtual void	Close() = 0;
	virtual void	Bind() = 0;
};

#endif
