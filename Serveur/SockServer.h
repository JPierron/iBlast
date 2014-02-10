#ifndef _SOCK_SERVER_
# define _SOCK_SERVER_

#include <iostream>
#include "iSocketUDP.h"

#ifndef _INCLUDER_SOCK_SERVER
# define _INCLUDER_SOCK_SERVER

#ifndef _WIN32
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <errno.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/ioctl.h>
	#include <netdb.h>
	#include <stdio.h>
	typedef int	Socket;

#else
	#include <winsock.h>
	#pragma comment(lib, "ws2_32.lib")
	typedef	SOCKET	Socket;

#endif	//_HOSTS

#endif

class						SockServer : public iSocketUDP
{
	std::string				_address;
	int						_port;
	sockaddr_in				_sockAddr;
	Socket					_socket;
public:
	SockServer(const int& port);
	~SockServer();
	void					Open();
	void					Close();
	void					Bind();
	unsigned int			RecvFrom(char* mess, sockaddr_in *from, int fromSize);
	unsigned int			SendTo(char* mess, sockaddr_in *dest, int destSize);
};

#endif //_A_SOCKET_UDP_
