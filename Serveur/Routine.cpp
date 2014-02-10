#include "Routine.h"
#include "iBlast.h"
#include "Serializer.hpp"

class	SockServer;
Routines::Routines(ThreadPool& tasksManager, DataManager< Packet >& data, SockServer& socket) : _tasksManager(tasksManager), _data(data), _socket(socket)
{
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_CONNECTION, &Routines::Connection));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_DISCONNECTION, &Routines::Disconnection));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_LAUNCH_GAME, &Routines::LaunchGame));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_POS_HERO, &Routines::PosHero));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_POS_SHOT, &Routines::PosShot));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_POS_SHOT_MOB, &Routines::PosShotMob));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_POS_ENN_I, &Routines::PosEnnI));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_POS_ENN_II, &Routines::PosEnnII));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_COLL_MOB_SHOT, &Routines::CollMobShot));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_COLL_HERO_SHOT, &Routines::CollHeroShot));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_COLL_MOB_HERO, &Routines::CollMobHero));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_SCORE, &Routines::Score));
}

Routines::~Routines()
{
}

void*	Routines::LaunchRoutine(void *arg)
{
	Routines*	Traitor = reinterpret_cast< Routines* >(arg);
	Traitor->RoutineTraitor();
	delete Traitor;
	return 0;
}

int	Routines::rPackType(char* buffer)
{
	int	packetType;
	memcpy(&packetType, buffer, 4);
	return packetType;
}

void	Routines::LaunchTraitor(const int&  Type, Packet& packet)
{
		(this->*_packetsTraitors[Type])(packet);
}

void	Routines::RoutineTraitor()
{
	while (1)
	{
		Sleep(1);
		this->_data.catchReceiver();
		if (!this->_data.getReceiver().empty())
		{
			Packet	*packet = new Packet(this->_data.getReceiver().front()._packet,	\
				this->_data.getReceiver().front()._fromPlayer);
			this->_data.getReceiver().pop_front();
			this->_data.freeReceiver();
			int	packetType = this->rPackType(packet->_packet);
			this->LaunchTraitor(packetType, *packet);
		}
		else
			this->_data.freeReceiver();
	}
}


//////////////////////////////////////////
// Redirection des paquets pour traitement

void	Routines::Connection(Packet &packet)
{
	Serializer< IBLAST::PackConnection >	Connection;
	Connection.SBinData(packet._packet);
	Connection.UnSerialize();
	this->_data.catchLaunched();
	if (this->_data.getLaunched() != true)
	{
		this->_data.catchClients();
		if (this->_data.getClients().size() < IBLAST::_MAX_PLAYER)
		{
			if (this->_data.getClients().find(Connection.GData()._playerName) == this->_data.getClients().end())
			{
				this->_data.getClients().insert(std::pair< std::string, sockaddr_in >(std::string(Connection.GData()._playerName), packet._fromPlayer));
				this->_data.catchMaster();
				if (this->_data.getMaster().length() == 0)
					this->AssignMaster(Connection.GData()._playerName, packet._fromPlayer);
				else
					this->AssignSlave(Connection.GData()._playerName, packet._fromPlayer);
				this->_data.freeMaster();
			}
			else
				this->PlayerAlreadyExist(packet._fromPlayer);
		}
		else
			this->ServerIsFull(packet._fromPlayer);
		this->_data.freeClients();
	}
	else
		this->AlreadyLaunched(packet._fromPlayer);
	this->_data.freeLaunched();
	delete &packet;
}

void	Routines::Disconnection(Packet &packet)
{
	Serializer< IBLAST::PackDisconnection >	Disconnection;
	Disconnection.SBinData(packet._packet);
	Disconnection.UnSerialize();
	this->_data.catchLaunched();
	if (this->_data.getLaunched() != true)
	{
		this->_data.catchMaster();
		if (this->_data.getMaster().compare(Disconnection.GData()._playerName) != 0)
			this->PlayerLeave(Disconnection.GData()._playerName);
		else
		{
			this->PlayerLeave(Disconnection.GData()._playerName);
			this->ReplaceMaster();
		}
		this->_data.freeMaster();
	}
	else
	{
		this->_data.catchMaster();
		if (this->_data.getMaster().compare(Disconnection.GData()._playerName) != 0)
			this->PlayerLeave(Disconnection.GData()._playerName);
		else
			this->EndGame();
		this->_data.freeMaster();
	}
	this->_data.freeLaunched();
	delete &packet;
}

void	Routines::LaunchGame(Packet& packet)
{
	Serializer< IBLAST::PackLaunchGame >	LaunchGame;
	LaunchGame.SBinData(packet._packet);
	LaunchGame.UnSerialize();
	this->_data.catchClients();
	std::map< std::string, sockaddr_in >::iterator it = this->_data.getClients().begin();
	for (; it != this->_data.getClients().end(); it++)
		if ((*it).first.compare(LaunchGame.GData()._playerName) != 0)
			this->_socket.SendTo(LaunchGame.GBinData(), &(*it).second, sizeof((*it).second));
	this->_data.freeClients();
	delete &packet;
}


//////////////////////////////////////
//Fonctions de traitements des paquets

void									Routines::PosHero(Packet& packet)
{
	Serializer< IBLAST::PackPosHero >	pos;
	pos.SBinData(packet._packet);
	pos.UnSerialize();
	this->_data.catchClients();
	std::map< std::string, sockaddr_in >::iterator	it = this->_data.getClients().begin();
	for (; it != this->_data.getClients().end(); it++)
		if ((*it).first.compare(pos.GData()._playerName) != 0)
			this->_socket.SendTo(packet._packet, &(*it).second, sizeof((*it).second));
	this->_data.freeClients();
	delete &packet;
}

void									Routines::PosShot(Packet& packet)
{
	Serializer< IBLAST::PackPosShot >	pos;
	pos.SBinData(packet._packet);
	pos.UnSerialize();
	this->_data.catchClients();
	std::map< std::string, sockaddr_in >::iterator	it = this->_data.getClients().begin();
	for (; it != this->_data.getClients().end(); it++)
		if ((*it).first.compare(pos.GData()._playerName) != 0)
			this->_socket.SendTo(packet._packet, &(*it).second, sizeof((*it).second));
	this->_data.freeClients();
	delete &packet;
}

void									Routines::PosShotMob(Packet& packet)
{
	Serializer< IBLAST::PackPosShotMob >	pos;
	pos.SBinData(packet._packet);
	pos.UnSerialize();
	this->_data.catchClients();
	std::map< std::string, sockaddr_in >::iterator	it = this->_data.getClients().begin();
	for (; it != this->_data.getClients().end(); it++)
	{
		this->_data.catchMaster();
		if ((*it).first.compare(this->_data.getMaster()) != 0)
			this->_socket.SendTo(packet._packet, &(*it).second, sizeof((*it).second));
		this->_data.freeMaster();
	}
	this->_data.freeClients();
	delete &packet;
}

void									Routines::PosEnnI(Packet& packet)
{
	Serializer< IBLAST::PackPosEnnI >	pos;
	pos.SBinData(packet._packet);
	pos.UnSerialize();
	this->_data.catchClients();
	std::map< std::string, sockaddr_in >::iterator	it = this->_data.getClients().begin();
	for (; it != this->_data.getClients().end(); it++)
	{
		this->_data.catchMaster();
		if ((*it).first.compare(this->_data.getMaster()) != 0)
			this->_socket.SendTo(packet._packet, &(*it).second, sizeof((*it).second));
		this->_data.freeMaster();
	}
	this->_data.freeClients();
	delete &packet;
}

void									Routines::PosEnnII(Packet& packet)
{
	Serializer< IBLAST::PackPosEnnII >	pos;
	pos.SBinData(packet._packet);
	pos.UnSerialize();
	this->_data.catchClients();
	std::map< std::string, sockaddr_in >::iterator	it = this->_data.getClients().begin();
	for (; it != this->_data.getClients().end(); it++)
	{
		this->_data.catchMaster();
		if ((*it).first.compare(this->_data.getMaster()) != 0)
			this->_socket.SendTo(packet._packet, &(*it).second, sizeof((*it).second));
		this->_data.freeMaster();
	}
	this->_data.freeClients();
	delete &packet;
}

void										Routines::CollMobHero(Packet& packet)
{
	Serializer< IBLAST::PackCollMobHero >	coll;
	coll.SBinData(packet._packet);
	coll.UnSerialize();
	this->_data.catchClients();
	std::map< std::string, sockaddr_in >::iterator	it = this->_data.getClients().begin();
	for (; it != this->_data.getClients().end(); it++)
	{
		this->_data.catchMaster();
		if ((*it).first.compare(this->_data.getMaster()) != 0)
			this->_socket.SendTo(packet._packet, &(*it).second, sizeof((*it).second));
		this->_data.freeMaster();
	}
	this->_data.freeClients();
	delete &packet;
}

void										Routines::CollHeroShot(Packet& packet)
{
	Serializer< IBLAST::PackCollHeroShot >	coll;
	coll.SBinData(packet._packet);
	coll.UnSerialize();
	this->_data.catchClients();
	std::map< std::string, sockaddr_in >::iterator	it = this->_data.getClients().begin();
	for (; it != this->_data.getClients().end(); it++)
	{
		this->_data.catchMaster();
		if ((*it).first.compare(this->_data.getMaster()) != 0)
			this->_socket.SendTo(packet._packet, &(*it).second, sizeof((*it).second));
		this->_data.freeMaster();
	}
	this->_data.freeClients();
	delete &packet;
}

void										Routines::CollMobShot(Packet& packet)
{
	Serializer< IBLAST::PackCollMobShot >	coll;
	coll.SBinData(packet._packet);
	coll.UnSerialize();
	this->_data.catchClients();
	std::map< std::string, sockaddr_in >::iterator	it = this->_data.getClients().begin();
	for (; it != this->_data.getClients().end(); it++)
	{
		this->_data.catchMaster();
		if ((*it).first.compare(this->_data.getMaster()) != 0)
			this->_socket.SendTo(packet._packet, &(*it).second, sizeof((*it).second));
		this->_data.freeMaster();
	}
	this->_data.freeClients();
	delete &packet;
}

void								Routines::Score(Packet& packet)
{
	Serializer< IBLAST::PackScore >	score;
	score.SBinData(packet._packet);
	score.UnSerialize();
	this->_data.catchClients();
	std::map< std::string, sockaddr_in >::iterator	it = this->_data.getClients().begin();
	for (; it != this->_data.getClients().end(); it++)
	{
		this->_data.catchMaster();
		if ((*it).first.compare(this->_data.getMaster()) != 0)
			this->_socket.SendTo(packet._packet, &(*it).second, sizeof((*it).second));
		this->_data.freeMaster();
	}
	this->_data.freeClients();
	delete &packet;
}

void	Routines::ServerIsFull(sockaddr_in &addr)
{
	Serializer< IBLAST::PackOkKo >	error;
	error.GData()._type = IBLAST::_OKKO;
	error.GData()._ok = false;
	std::string err("Le serveur est plein.");
	memset(error.GData()._mess, '\0', IBLAST::_MAX_ERROR_LEN);
	memcpy(error.GData()._mess, err.c_str(), IBLAST::_MAX_ERROR_LEN);
	error.Serialize();
	this->_socket.SendTo(error.GBinData(), &addr, sizeof(addr));
}

void	Routines::AlreadyLaunched(sockaddr_in &addr)
{
	Serializer< IBLAST::PackOkKo >	error;
	error.GData()._type = IBLAST::_OKKO;
	error.GData()._ok = false;
	std::string err("La partie est deja lancee.");
	memset(error.GData()._mess, '\0', IBLAST::_MAX_ERROR_LEN);
	memcpy(error.GData()._mess, err.c_str(), IBLAST::_ERR_LAUNCHED_LEN);
	error.Serialize();
	this->_socket.SendTo(error.GBinData(), &addr, sizeof(addr));
}

void	Routines::PlayerAlreadyExist(sockaddr_in &addr)
{
	Serializer< IBLAST::PackOkKo >	error;
	error.GData()._type = IBLAST::_OKKO;
	error.GData()._ok = false;
	std::string err("Pseudo deja utilise.");
	memset(error.GData()._mess, '\0', IBLAST::_MAX_ERROR_LEN);
	memcpy(error.GData()._mess, err.c_str(), IBLAST::_ERR_NAME_TAKEN_LEN);
	error.Serialize();
	this->_socket.SendTo(error.GBinData(), &addr, sizeof(addr));
}

void	Routines::AssignMaster(const std::string &player, sockaddr_in &addr)
{
	Serializer< IBLAST::PackOkKo >	accept;
	accept.GData()._type = IBLAST::_OKKO;
	accept.GData()._ok = true;
	accept.GData()._master = true;
	accept.Serialize();
	this->_data.catchMaster();
	this->_data.getMaster() = player;
	this->_data.freeMaster();
	this->_socket.SendTo(accept.GBinData(), &addr, sizeof(addr));
}

void	Routines::AssignSlave(const std::string &player, sockaddr_in &addr)
{
	Serializer< IBLAST::PackOkKo >	accept;
	accept.GData()._type = IBLAST::_OKKO;
	accept.GData()._ok = true;
	accept.GData()._master = false;
	accept.Serialize();
	this->_socket.SendTo(accept.GBinData(), &addr, sizeof(addr));

	Serializer< IBLAST::PackNewPlayer >	newPlayer;
	newPlayer.GData()._type = IBLAST::_NEW_PLAYER;
	memset(newPlayer.GData()._playerName, '\0', IBLAST::_MAX_NAME_LEN);
	memcpy(newPlayer.GData()._playerName, player.c_str(), IBLAST::_MAX_NAME_LEN);
	newPlayer.Serialize();
	this->_data.catchClients();
	std::map< std::string, sockaddr_in >::iterator it = this->_data.getClients().begin();
	for (; it != this->_data.getClients().end(); it++)
	{
		Serializer< IBLAST::PackPlayer >	oldPlayer;
		oldPlayer.GData()._type = IBLAST::_PLAYER;
		this->_data.catchMaster();
		if ((*it).first.compare(this->_data.getMaster()) != 0)
			oldPlayer.GData()._master = false;
		else
			oldPlayer.GData()._master = true;
		this->_data.freeMaster();
		memset(oldPlayer.GData()._playerName, '\0', IBLAST::_MAX_NAME_LEN);
		memcpy(oldPlayer.GData()._playerName, (*it).first.c_str(), IBLAST::_MAX_NAME_LEN);
		oldPlayer.Serialize();
		this->_socket.SendTo(newPlayer.GBinData(), &(*it).second, sizeof((*it).second));
		this->_socket.SendTo(oldPlayer.GBinData(), &addr, sizeof(addr));
	}
	this->_data.getClients().insert(std::pair< std::string, sockaddr_in >(player, addr));
	this->_data.freeClients();
}

void	Routines::PlayerLeave(const std::string &player)
{
	Serializer< IBLAST::PackPlayerLeave >	playerLeave;
	playerLeave.GData()._type = IBLAST::_PLAYER_LEAVE;
	memset(playerLeave.GData()._playerName, '\0', IBLAST::_MAX_NAME_LEN);
	memcpy(playerLeave.GData()._playerName, player.c_str(), IBLAST::_MAX_NAME_LEN);
	playerLeave.Serialize();
	this->_data.catchClients();
	this->_data.getClients().erase(this->_data.getClients().find(player));
	std::map< std::string, sockaddr_in >::iterator it = this->_data.getClients().begin();
	for (; it != this->_data.getClients().end(); it++)
		this->_socket.SendTo(playerLeave.GBinData(), &(*it).second, sizeof((*it).second));
	this->_data.freeClients();
}

void	Routines::ReplaceMaster()
{
	Serializer< IBLAST::PackNewMaster >	newMaster;
	newMaster.GData()._type = IBLAST::_NEW_MASTER;
	memset(newMaster.GData()._playerName, '\0', IBLAST::_MAX_NAME_LEN);
	this->_data.catchClients();
	if (!this->_data.getClients().empty())
	{
		memcpy(newMaster.GData()._playerName, (*this->_data.getClients().begin()).first.c_str(), IBLAST::_MAX_NAME_LEN);
		newMaster.Serialize();
		std::map< std::string, sockaddr_in >::iterator it = this->_data.getClients().begin();
		for (; it != this->_data.getClients().end(); it++)
			this->_socket.SendTo(newMaster.GBinData(), &(*it).second, sizeof((*it).second));
		this->_data.freeClients();
		this->_data.catchMaster();
		this->_data.getMaster() = newMaster.GData()._playerName;
		this->_data.freeMaster();
	}
	else
	{
		this->_data.freeClients();
		this->_data.catchMaster();
		this->_data.getMaster() = "";
		this->_data.freeMaster();
	}
}

void	Routines::EndGame()
{
	this->_data.catchLaunched();
	this->_data.getLaunched() = false;
	this->_data.freeLaunched();
	Serializer< IBLAST::PackEndGame >	endGame;
	endGame.GData()._type = IBLAST::_PLAYER_LEAVE;
	memset(endGame.GData()._playerName, '\0', IBLAST::_MAX_NAME_LEN);
	this->_data.catchClients();
	memcpy(endGame.GData()._playerName, (*this->_data.getClients().begin()).first.c_str(), IBLAST::_MAX_NAME_LEN);
	endGame.Serialize();
	std::map< std::string, sockaddr_in >::iterator it = this->_data.getClients().begin();
	for (; it != this->_data.getClients().end(); it++)
		this->_socket.SendTo(endGame.GBinData(), &(*it).second, sizeof((*it).second));
	this->_data.getClients().clear();
	this->_data.freeClients();
	this->_data.catchMaster();
	this->_data.getMaster() = "";
	this->_data.freeMaster();
}
