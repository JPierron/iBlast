#ifndef _PACKET_
# define _PACKET_

#include <iostream>
#include "SockServer.h"
#include "iBlast.h"

struct							Packet
{
	char						_packet[IBLAST::_MAX_BUFF_LEN];
	sockaddr_in					_fromPlayer;

	Packet()
	{
	}
	Packet(const char* packet, const sockaddr_in& fromPlayer)
	{
		memset(this->_packet, 0, IBLAST::_MAX_BUFF_LEN);
		memcpy(this->_packet, packet, IBLAST::_MAX_BUFF_LEN);
		this->_fromPlayer.sin_addr.s_addr = fromPlayer.sin_addr.s_addr;
		this->_fromPlayer.sin_family = fromPlayer.sin_family;
		this->_fromPlayer.sin_port = fromPlayer.sin_port;
	}
};

#endif
