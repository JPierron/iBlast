#ifndef _SOCK_SERVER_
# define _SOCK_SERVER_

#include <iostream>
#include "iSocketUDP.h"

#ifndef _INCLUDER_SOCK_CLIENT
# define _INCLUDER_SOCK_CLIENT

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

class						SockClient : public iSocketUDP
{
	std::string				_address;
	int						_port;
	sockaddr_in				_sockAddr;
	Socket					_socket;
public:
	SockClient();
	~SockClient();
	void					SetUp(const int& port, const std::string& address);
	void					Open();
	void					Close();
	unsigned int			RecvFrom(char* mess);
	unsigned int			SendTo(char* mess);
};

#endif //_A_SOCKET_UDP_
