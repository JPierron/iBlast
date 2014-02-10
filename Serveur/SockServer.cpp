#include "SockServer.h"

SockServer::SockServer(const int& port)
{
	#ifdef _WIN32
		WSADATA wsaData;
		WORD wVersion = MAKEWORD(2,0);
		if(WSAStartup(wVersion, &wsaData) != 0)
			std::cerr <<"WSAStartup error" << std::endl;
	#endif
	_port = port;
}

SockServer::~SockServer()
{
	#ifdef _WIN32
		WSACleanup();
	#endif
}

void	SockServer::Open()
{
	this->_sockAddr.sin_addr.s_addr = INADDR_ANY;
	this->_sockAddr.sin_family = AF_INET;
	this->_sockAddr.sin_port = htons(this->_port);
	this->_socket = socket(AF_INET, SOCK_DGRAM, 0);
}

void	SockServer::Close()
{
	#ifndef _WIN32
		close(this->_socket);
	#else
		closesocket(this->_socket);
	#endif
}

void	SockServer::Bind()
{
	#ifndef _WIN32
		if (bind(this->_socket, (sockaddr*)&this->_sockAddr, sizeof(this->_sockAddr)) < 0)
	#else
		if (bind(this->_socket, (SOCKADDR*)&this->_sockAddr, sizeof(this->_sockAddr)) == SOCKET_ERROR)
	#endif
			std::cerr << "Bind problem" << std::endl;
}

unsigned int	SockServer::RecvFrom(char* mess, sockaddr_in* from, int fromSize)
{
	#ifndef _WIN32
		return recvfrom(this->_socket, (void*)mess, 512, NULL, (sockaddr*)from, &fromSize);
	#else
		return recvfrom(this->_socket, mess, 512, NULL, (SOCKADDR*)from, &fromSize);
	#endif
}

unsigned int	SockServer::SendTo(char* mess, sockaddr_in* dest, int destSize)
{
	#ifndef _WIN32
		return sendto(this->_socket, (void*)mess, 512, NULL, (sockaddr*)dest, destSize);
	#else
		return sendto(this->_socket, mess, 512, NULL, (SOCKADDR*)dest, destSize);
	#endif
}
