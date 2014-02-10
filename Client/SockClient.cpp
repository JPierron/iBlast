#include "SockClient.h"

SockClient::SockClient()
{
	#ifdef _WIN32
		WSADATA wsaData;
		WORD wVersion = MAKEWORD(2,0);
		if(WSAStartup(wVersion, &wsaData) != 0)
			std::cerr <<"WSAStartup error" << std::endl;
	#endif
}

SockClient::~SockClient()
{
	#ifdef _WIN32
		WSACleanup();
	#endif
}

void	SockClient::SetUp(const int& port, const std::string& address)
{
	this->_address = address;
	this->_port = port;
}

void	SockClient::Open()
{
	this->_sockAddr.sin_addr.s_addr = inet_addr(this->_address.c_str());
	this->_sockAddr.sin_family = AF_INET;
	this->_sockAddr.sin_port = htons(this->_port);
	this->_socket = socket(AF_INET, SOCK_DGRAM, 0);
}

void	SockClient::Close()
{
	#ifndef _WIN32
		close(this->_socket);
	#else
		closesocket(this->_socket);
	#endif
}

unsigned int	SockClient::RecvFrom(char* mess)
{
	int	size = sizeof(this->_sockAddr);
	#ifndef _WIN32
		return recvfrom(this->_socket, (void*)mess, 512, NULL, (sockaddr*)&this->_sockAddr, &size);
	#else
		return recvfrom(this->_socket, mess, 512, NULL, (SOCKADDR*)&this->_sockAddr, &size);
	#endif
}

unsigned int	SockClient::SendTo(char* mess)
{
	#ifndef _WIN32
		return sendto(this->_socket, (void*)mess, 512, NULL, (sockaddr*)&this->_sockAddr, sizeof(this->_sockAddr));
	#else
		return sendto(this->_socket, mess, 512, NULL, (SOCKADDR*)&this->_sockAddr, sizeof(this->_sockAddr));
	#endif
}
