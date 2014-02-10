#ifndef _Entity_
#define _Entity_
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Plat;
static int entities;
class Entities
{
	int					id;
	int					type;
	std::string			name;
	float				tmp_x;
	float				tmp_y;
public:
	int					ok;
	Entities(int, std::string);
	~Entities();
	int						getId();
	int						getType();
	const std::string&		getName();
	void					sId(int _id);
	virtual	sf::Drawable*	getEntities() = 0;
	virtual float			getPosX() = 0;
	virtual float			getPosY() = 0;
	virtual sf::Sprite		getSprite() = 0;
	virtual	int				getLife() = 0;
	virtual	void			setLife(int) = 0;
	virtual void			playEvent(Plat&) = 0;
	virtual int				getIdT() = 0;
	virtual int				getIdMob() = 0;
	virtual std::string		getPlayName() = 0;
	virtual void			setPos(float, float) = 0;
	float					getTMPx();
	float					getTMPy();
	void					sTMPx(float);
	void					sTMPy(float);
};

#endif
