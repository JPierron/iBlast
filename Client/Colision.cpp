#include "Colision.h"

Colision::Colision(ThreadSafeData< std::list<Entities*> >& _ent, Client& _IBlast) : SEnts(_ent), IBlast(_IBlast)
{
	PtrMeth.insert(std::make_pair(IBLAST::_POS_SHOT, &Colision::doShootMob));	
	PtrMeth.insert(std::make_pair(IBLAST::_POS_ENN_I, &Colision::doMobHero));	
	PtrMeth.insert(std::make_pair(IBLAST::_POS_SHOT_MOB, &Colision::doHeroShot));
	state = 0;
	tuile = 0;
}

Colision::~Colision()
{
}

int	Colision::LaunchCheck(void* arg)
{
	Colision*	Traitor = reinterpret_cast< Colision* >(arg);
	Traitor->StartCheck();
	delete Traitor;
	return 0;
}	

bool	Colision::doShootMob(Entities& arg, Entities& arg_cmp)
{
	if (arg.getType() == MAZZELTOF || arg.getType() == PEPELOUNI)
	{
		Serializer<IBLAST::PackCollMobShot> ser;

		ser.GData()._type = IBLAST::_COLL_MOB_SHOT;
		ser.GData()._idMob = arg.getIdT();
		ser.GData()._idShot = arg_cmp.getIdT();
		memset(ser.GData()._playerName, '/0', IBLAST::_MAX_NAME_LEN);
		memcpy(ser.GData()._playerName, arg_cmp.getPlayName().c_str(), IBLAST::_MAX_NAME_LEN); 
		ser.Serialize();
		this->IBlast.gSocketNFO().SendTo(ser.GBinData());
		return (true);
	}
	return (false);
}

bool	Colision::doHeroShot(Entities& arg, Entities& arg_cmp)
{
	if (arg.getType() != MAZZELTOF && arg.getType() != PEPELOUNI)
	{
		Serializer<IBLAST::PackCollHeroShot> ser;
		ser.GData()._type = IBLAST::_COLL_HERO_SHOT;
		ser.GData()._idMob = arg_cmp.getIdMob();
		ser.GData()._idShot = arg_cmp.getIdT();
		memset(ser.GData()._playerName, '/0', IBLAST::_MAX_NAME_LEN);
		memcpy(ser.GData()._playerName, arg.getName().c_str(), IBLAST::_MAX_NAME_LEN); 
		ser.Serialize();
		this->IBlast.gSocketNFO().SendTo(ser.GBinData());
		return (true);
	}
	return false;
}


char*	Colision::createPacket(char* _bin)
{
	char*	packet = (char*)malloc(IBLAST::_MAX_BUFF_LEN);
	memset(packet, '\0', IBLAST::_MAX_BUFF_LEN);
	memcpy(packet, _bin, IBLAST::_MAX_BUFF_LEN);
	return packet;
}

bool	Colision::doMobHero(Entities& arg, Entities& arg_cmp)
{
	/*	Serializer<IBLAST::PackCollMobHero> ser;
	ser.GData()._type = IBLAST::_COLL_MOB_HERO;
	ser.GData()._idMob = arg_cmp.getIdMob();
	memset(ser.GData()._playerName, '/0', IBLAST::_MAX_NAME_LEN);
	memcpy(ser.GData()._playerName, arg.getName().c_str(), IBLAST::_MAX_NAME_LEN); 
	ser.Serialize();
	this->IBlast.gSocketNFO().SendTo(ser.GBinData());
	return (true);
	*/
	return false;
}

void	Colision::SendPosMob()
{
	std::list<Entities*>::iterator it = this->SEnts.GetData().begin();

	for (; it != this->SEnts.GetData().end(); it++)
	{
		if ((*it)->getType() == IBLAST::_POS_ENN_I ||(*it)->getType() == IBLAST::_POS_ENN_II)
		{
			Serializer<IBLAST::PackPosEnn1> ser;
			ser.GData()._type = IBLAST::_POS_ENN_I;
			ser.GData()._id = (*it)->getIdT();
			ser.GData()._hp = (*it)->getLife();
			ser.GData()._x = (*it)->getPosX();
			ser.GData()._y = (*it)->getPosY();
			ser.Serialize();
			this->IBlast.gSocketNFO().SendTo(ser.GBinData());
		}
		if ((*it)->getType() == IBLAST::_POS_SHOT_MOB)
		{
			Serializer<IBLAST::PackPosShotMob> ser;
			ser.GData()._type = IBLAST::_POS_SHOT_MOB;
			ser.GData()._id = (*it)->getIdT();
			ser.GData()._idMob = (*it)->getIdMob();
			ser.GData()._typeMob = 1;
			ser.GData()._x = (int)(*it)->getPosX();
			ser.GData()._y = (int)(*it)->getPosY();
			ser.Serialize();
			this->IBlast.gSocketNFO().SendTo(ser.GBinData());
		}
	}
}

void	Colision::AddEntByTuile()
{
	if (this->tuile % 700 == 0 && this->tuile < 5000)
		this->SEnts.GetData().push_back(new MazzelTof(1, 120, 800, (float)(rand() % 600)));
	if (this->tuile == 7000)
		this->SEnts.GetData().push_back(new Pepel());
}

sf::IntRect Colision::getIntRect(const sf::Sprite &sprite) 
{ 
	const sf::Vector2f &pos(sprite.GetPosition()); 
	const sf::IntRect  &sub_rect(sprite.GetSubRect()); 
	sf::IntRect int_rect((int)pos.x, (int)pos.y, (int)(pos.x + sub_rect.GetWidth()), (int)(pos.y + sub_rect.GetHeight()));

	return (int_rect); 
} 

void	Colision::StartCheck()
{

	while (1)
	{
		Sleep(10);
		this->tuile += 1;
		this->SEnts.CatchData();
		std::list<Entities*>::iterator it_check = this->SEnts.GetData().begin();
		bool Col = false;
		for (; it_check != this->SEnts.GetData().end(); it_check++)
		{
			std::list<Entities*>::iterator it_cmp = this->SEnts.GetData().begin();
			if ((*it_check)->getType() != BACKG)
			{
				for (; it_cmp != this->SEnts.GetData().end(); it_cmp++)
				{	
					if ((*it_cmp)->getId() != (*it_check)->getId() && (*it_cmp)->getType() != BACKG &&
						this->getIntRect((*it_check)->getSprite()).Intersects(this->getIntRect((*it_cmp)->getSprite())))
					{		
						for (std::map<int,PtrCol>::iterator it = this->PtrMeth.begin(); it != this->PtrMeth.end(); it++)	
						{
							if ((*it_check)->getType() == it->first)
							{
								PtrCol ptr = it->second;
								if ((this->*ptr)((*(*it_cmp)),(*(*it_check))) == true)
								{
									delete (*it_cmp);
									delete (*it_check);
									this->SEnts.GetData().erase(it_cmp);
									this->SEnts.GetData().erase(it_check);
									it_check = this->SEnts.GetData().begin();
									it_cmp = this->SEnts.GetData().begin();
								}
							}
						}
					}

				}
			}
		}
		this->AddEntByTuile();
		this->SendPosMob();
		this->SEnts.FreeData();
	}
}

int		Colision::getState()
{
	return this->state;
}
