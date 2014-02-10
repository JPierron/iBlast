#ifndef _ROUTINES_
# define _ROUTINES_

#include "Packet.hpp"
//#include "ThreadPool.h"
//#include "DataManager.hpp"
//#include "SockClient.h"
#include "Client.h"

class	Routines;
typedef	void	(Routines::*PacketsTraitor)(char* packet);

class	Client;
//class	SockClient;
class								Routines
{
	std::map< int, PacketsTraitor >	_packetsTraitors;
	Client&							IBlast;
public:
	Routines(Client& rtype);
	~Routines();
	int								rPackType(char *buffer);
	static void*					LaunchReceiver(void *arg);
	static void*					LaunchSender(void *arg);
	void							RoutineReceiver();
	void							RoutineSender();
	void							LaunchTraitor(const int& Type, char* packet);

	//////////////////////////////////////
	//Fonctions de traitements des paquets

	Entities*						CheckEntities(int _type, int _id_t, std::string name);
	void							PosHero(char* packet);
	void							PosShot(char* packet);
	void							PosEnnI(char* packet);
	void							PosEnnII(char* packet);
	void							CollMobHero(char* packet);
	void							CollMobShot(char* packet);
	void							PosShotMob(char* packet);
	void							CollHeroShot(char* packet);

	void							Score(char* packet);

	//////////////////////////////////////////
	// Redirection des paquets pour traitement

	void							Player(char* packet);
	void							NewPlayer(char* packet);
	void							LaunchGame(char* packet);
	void							PlayerLeave(char* packet);
	void							NewMaster(char* packet);
};

#endif
