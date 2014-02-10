#include "Routine.h"
#include "iBlast.h"
#include "Serializer.hpp"
#include "FakeEntitie.h"

class	SockClient;
Routines::Routines(Client& iblast) : IBlast(iblast)
{
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_PLAYER, &Routines::Player));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_NEW_PLAYER, &Routines::NewPlayer));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_PLAYER_LEAVE, &Routines::PlayerLeave));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_LAUNCH_GAME, &Routines::LaunchGame));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_NEW_MASTER, &Routines::NewMaster));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_POS_HERO, &Routines::PosHero));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_POS_SHOT, &Routines::PosShot));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_POS_SHOT_MOB, &Routines::PosShotMob));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_POS_ENN_I, &Routines::PosEnnI));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_POS_ENN_II, &Routines::PosEnnII));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_COLL_MOB_HERO, &Routines::CollMobHero));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_COLL_MOB_SHOT, &Routines::CollMobShot));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_COLL_HERO_SHOT, &Routines::CollHeroShot));
	_packetsTraitors.insert(std::pair< int, PacketsTraitor >(IBLAST::_SCORE, &Routines::Score));
}

Routines::~Routines()
{
}

void*	Routines::LaunchReceiver(void *arg)
{
	Routines*	Traitor = reinterpret_cast< Routines* >(arg);
	Traitor->RoutineReceiver();
	delete Traitor;
	return 0;
}

void*	Routines::LaunchSender(void *arg)
{
	Routines*	Traitor = reinterpret_cast< Routines* >(arg);
	Traitor->RoutineSender();
	delete Traitor;
	return 0;
}

int	Routines::rPackType(char* buffer)
{
	int	packetType;
	memcpy(&packetType, buffer, 4);
	return packetType;
}

void	Routines::LaunchTraitor(const int& Type, char* packet)
{
	(this->*_packetsTraitors[Type])(packet);
}

void	Routines::RoutineReceiver()
{
	while (1)
	{
		Sleep(1);
		Packet	packet;
		this->IBlast.gSocketNFO().RecvFrom(packet._packet);
		this->IBlast.gDatas().catchReceiver();
		this->IBlast.gDatas().getReceiver().push_back(packet._packet);
		this->IBlast.gDatas().freeReceiver();
	}
}

void	Routines::RoutineSender()
{
	while (1)
	{
		Sleep(1);
		this->IBlast.gDatas().catchReceiver();
		if (!this->IBlast.gDatas().getReceiver().empty())
		{
			int	packetType = this->rPackType(this->IBlast.gDatas().getReceiver().front());
			this->LaunchTraitor(packetType, this->IBlast.gDatas().getReceiver().front());
			this->IBlast.gDatas().getReceiver().pop_front();
			this->IBlast.gDatas().freeReceiver();
		}
		else
			this->IBlast.gDatas().freeReceiver();
	}
}


//////////////////////////////////////////
// Redirection des paquets pour traitement

Entities*								Routines::CheckEntities(int _type, int _id_t, std::string _name)
{
	std::list<Entities*>::iterator it = this->IBlast.gGui().Game->getWManager().getEntities().begin();

	for (; it != this->IBlast.gGui().Game->getWManager().getEntities().end(); it++)
	{
		if ((*it)->getType() == _type && (((*it)->getIdT() == _id_t && (*it)->getType() != IBLAST::_POS_HERO) || ((*it)->getType() == IBLAST::_POS_HERO && (*it)->getName().compare(_name) == 0)))
			return (*it);	
	}
	return (NULL);
}

void									Routines::PosHero(char* packet)
{
	Serializer< IBLAST::PackPosHero >	pos;
	pos.SBinData(packet);
	pos.UnSerialize();
	this->IBlast.gGui().Game->getWManager().catchEntities();
	Entities *Ent = this->CheckEntities(pos.GData()._type, 0, pos.GData()._playerName);
	if (Ent == NULL)
		this->IBlast.gGui().Game->getWManager().newEntities(new FakeEntitie(0, pos.GData()._type, pos.GData()._playerName, 0));
	else
		Ent->setPos(pos.GData()._x, pos.GData()._y);
	this->IBlast.gGui().Game->getWManager().freeEntities();
}

void									Routines::PosShot(char* packet)
{
	Serializer< IBLAST::PackPosShot >	pos;
	pos.SBinData(packet);
	pos.UnSerialize();
	this->IBlast.gGui().Game->getWManager().catchEntities();
	Entities *Ent = this->CheckEntities(pos.GData()._type, pos.GData()._id, "l");
	if (Ent == NULL)
		this->IBlast.gGui().Game->getWManager().newEntities(new FakeEntitie(pos.GData()._id, pos.GData()._type, pos.GData()._playerName, 0));
	else
		Ent->setPos((float)pos.GData()._x, (float)pos.GData()._y);
	this->IBlast.gGui().Game->getWManager().freeEntities();
}

void									Routines::PosShotMob(char* packet)
{
	Serializer< IBLAST::PackPosShotMob >	pos;
	pos.SBinData(packet);
	pos.UnSerialize();
	this->IBlast.gGui().Game->getWManager().catchEntities();
	Entities *Ent = this->CheckEntities(pos.GData()._type, pos.GData()._id, "l");
	if (Ent == NULL)
		this->IBlast.gGui().Game->getWManager().newEntities(new FakeEntitie(pos.GData()._id, pos.GData()._type, "", 0));
	else
		Ent->setPos((float)pos.GData()._x, (float)pos.GData()._y);
	this->IBlast.gGui().Game->getWManager().freeEntities();
}

void									Routines::PosEnnI(char* packet)
{
	Serializer< IBLAST::PackPosEnnI >	pos;
	pos.SBinData(packet);
	pos.UnSerialize();
	this->IBlast.gGui().Game->getWManager().catchEntities();
	Entities *Ent = this->CheckEntities(pos.GData()._type, pos.GData()._id, "");
	if (Ent == NULL)
		this->IBlast.gGui().Game->getWManager().newEntities(new FakeEntitie(pos.GData()._id, pos.GData()._type, "", 0));
	else
		Ent->setPos(pos.GData()._x, pos.GData()._y);
	this->IBlast.gGui().Game->getWManager().freeEntities();
}

void									Routines::PosEnnII(char* packet)
{
	Serializer< IBLAST::PackPosEnnII >	pos;
	pos.SBinData(packet);
	pos.UnSerialize();
	this->IBlast.gGui().Game->getWManager().catchEntities();
	Entities *Ent = this->CheckEntities(pos.GData()._type, pos.GData()._id, "");
	if (Ent == NULL)
		this->IBlast.gGui().Game->getWManager().newEntities(new FakeEntitie(pos.GData()._id, pos.GData()._type, "", 0));
	else
		Ent->setPos(pos.GData()._x, pos.GData()._y);
	this->IBlast.gGui().Game->getWManager().freeEntities();
}

void										Routines::CollMobHero(char* packet)
{
	Serializer< IBLAST::PackCollMobHero >	coll;
	coll.SBinData(packet);
	coll.UnSerialize();
	this->IBlast.gGui().Game->getWManager().catchEntities();
	for (std::list<Entities*>::iterator it = this->IBlast.gGui().Game->getWManager().getEntities().begin();
		it != this->IBlast.gGui().Game->getWManager().getEntities().end(); it++)
	{
		if ((*it)->getType() == MAZZELTOF && (*it)->getIdT() == coll.GData()._idMob)	
		{
			this->IBlast.gGui().Game->getWManager().getEntities().erase(it);
			delete (*it);		
			it = this->IBlast.gGui().Game->getWManager().getEntities().begin();
		}		
		if ((*it)->getName() == coll.GData()._playerName)		
			if ((*it)->getLife() == 0)
			{
				this->IBlast.gGui().Game->getWManager().getEntities().erase(it);
				delete (*it);
				it = this->IBlast.gGui().Game->getWManager().getEntities().begin();
			}
			else
				(*it)->setLife((*it)->getLife() - 1);
	}
	this->IBlast.gGui().Game->getWManager().freeEntities();
}

void										Routines::CollMobShot(char* packet)
{
	Serializer< IBLAST::PackCollMobShot >	coll;
	coll.SBinData(packet);
	coll.UnSerialize();
	this->IBlast.gGui().Game->getWManager().catchEntities();
	for (std::list<Entities*>::iterator it = this->IBlast.gGui().Game->getWManager().getEntities().begin();
		it != this->IBlast.gGui().Game->getWManager().getEntities().end(); it++)
	{
		if ((*it)->getType() == IBLAST::_POS_ENN_I && (*it)->getIdT() == coll.GData()._idMob)	
		{
			delete (*it);
			this->IBlast.gGui().Game->getWManager().getEntities().erase(it);
			it = this->IBlast.gGui().Game->getWManager().getEntities().begin();
		}		
		if ((*it)->getPlayName() == coll.GData()._playerName && (*it)->getIdT() == coll.GData()._idShot)
		{
			delete (*it);
			this->IBlast.gGui().Game->getWManager().getEntities().erase(it);
			it = this->IBlast.gGui().Game->getWManager().getEntities().begin();		
		}	
	}

	this->IBlast.gGui().Game->getWManager().freeEntities();
}

void										Routines::CollHeroShot(char* packet)
{
	Serializer< IBLAST::PackCollHeroShot >	coll;
	coll.SBinData(packet);
	coll.UnSerialize();
	this->IBlast.gGui().Game->getWManager().catchEntities();
	this->IBlast.gGui().Game->getWManager().freeEntities();
}

void								Routines::Score(char* packet)
{
	Serializer< IBLAST::PackScore >	score;
	score.SBinData(packet);
	score.UnSerialize();
	this->IBlast.gGui().Game->getWManager().catchEntities();
	this->IBlast.gGui().Game->getWManager().freeEntities();
}

//////////////////////////////////////
//Fonctions de traitements des paquets

void	Routines::Player(char* packet)
{
	Serializer< IBLAST::PackPlayer >	player;
	player.SBinData(packet);
	player.UnSerialize();
	this->IBlast.gDatas().catchClients();
	this->IBlast.gDatas().getClients().insert(std::pair< std::string, bool >(std::string(player.GData()._playerName), player.GData()._master));
	this->IBlast.gDatas().freeClients();
}

void	Routines::NewPlayer(char* packet)
{
	Serializer< IBLAST::PackNewPlayer >	player;
	player.SBinData(packet);
	player.UnSerialize();
	this->IBlast.gDatas().catchClients();
	this->IBlast.gDatas().getClients().insert(std::pair< std::string, bool >(std::string(player.GData()._playerName), false));
	this->IBlast.gDatas().freeClients();
}

void	Routines::LaunchGame(char* packet)
{
	Serializer< IBLAST::PackLaunchGame >	launch;
	launch.SBinData(packet);
	launch.UnSerialize();
	this->IBlast.gGui().CurrentWindow = GAME;
}

void	Routines::PlayerLeave(char* packet)
{
	Serializer< IBLAST::PackPlayerLeave >	player;
	player.SBinData(packet);
	player.UnSerialize();
	this->IBlast.gDatas().catchClients();
	this->IBlast.gDatas().getClients().erase(this->IBlast.gDatas().getClients().find(player.GData()._playerName));
	this->IBlast.gDatas().freeClients();
}

void	Routines::NewMaster(char* packet)
{
	Serializer< IBLAST::PackNewMaster >	player;
	player.SBinData(packet);
	player.UnSerialize();
	this->IBlast.gDatas().catchClients();
	if (this->IBlast._Pseudo.compare(player.GData()._playerName) == 0)
	{
		this->IBlast.gDatas().catchMaster();
		this->IBlast.gDatas().getMaster() = true;
		this->IBlast.gDatas().freeMaster();
	}
	this->IBlast.gDatas().getClients()[player.GData()._playerName] = true;
	this->IBlast.gDatas().freeClients();
}
 