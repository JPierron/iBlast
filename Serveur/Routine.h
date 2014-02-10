#ifndef _ROUTINES_
# define _ROUTINES_

#include "ThreadPool.h"
#include "Packet.hpp"
#include "DataManager.hpp"
#include "SockServer.h"

class	Routines;
typedef	void	(Routines::*PacketsTraitor)(Packet& packet);

class	SockServer;
class								Routines
{
	std::map< int, PacketsTraitor >	_packetsTraitors;
	ThreadPool&						_tasksManager;
	DataManager< Packet >&			_data;
	SockServer&						_socket;
public:
	Routines(ThreadPool& tasksManager, DataManager< Packet >& data, SockServer& socket);
	~Routines();
	static void*					LaunchRoutine(void *arg);
	int								rPackType(char *buffer);
	void							RoutineTraitor();
	void							LaunchTraitor(const int& Type, Packet& packet);

	//////////////////////////////////////
	//Fonctions de traitements des paquets

	void							ServerIsFull(sockaddr_in& addr);
	void							AlreadyLaunched(sockaddr_in& addr);
	void							PlayerAlreadyExist(sockaddr_in& addr);
	void							AssignMaster(const std::string& player, sockaddr_in& addr);
	void							AssignSlave(const std::string& player, sockaddr_in& addr);
	void							PlayerLeave(const std::string& player);
	void							ReplaceMaster();
	void							EndGame();

	//////////////////////////////////////////
	// Redirection des paquets pour traitement

	void							Connection(Packet& packet);
	void							Disconnection(Packet& packet);
	void							LaunchGame(Packet& packet);
	void							PosHero(Packet& packet);
	void							PosShot(Packet& packet);
	void							PosShotMob(Packet& packet);
	void							PosEnnI(Packet& packet);
	void							PosEnnII(Packet& packet);
	void							CollMobHero(Packet& packet);
	void							CollHeroShot(Packet& packet);
	void							CollMobShot(Packet& packet);
	void							Score(Packet& packet);
};

#endif
