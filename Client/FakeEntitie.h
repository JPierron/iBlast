#ifndef _FAKEENTITIE_
#define _FAKEENTITIE_
#include "Entities.h"
#include "iBlast.h"

class FakeEntitie;
typedef void (FakeEntitie::*PtrFake)();

class FakeEntitie 
	: public Entities
{
	int						id_t;
	int						type;
	int						type_shot;
	std::string				name;
	int						life;
	sf::Vector2<float>		pos;
	sf::Image				img;
	sf::Sprite				sprite;
	std::map<int, PtrFake>	PtrMeth;
public:
	FakeEntitie(int _id_t, int type, std:: string _name, int _typeshot);
	~FakeEntitie();
	void			doHero();
	void			doMazzelTof();
	void			doPepelouni();
	void			doShot();
	void			doShotMob();
	void			setPos(float x, float y);
	void			playEvent(Plat&);
	sf::Drawable*	getEntities();
	int				getLife();
	float			getPosX();
	float			getPosY();
	sf::Sprite		getSprite();
	void			setLife(int);
	int				getIdT();
	int				getIdMob();	
	std::string		getPlayName();
};

#endif