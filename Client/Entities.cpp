#include "Entities.h"

Entities::Entities(int _type, std::string _name)
{
	id = entities++;
	type = _type;
	name = _name;
	ok = 0;
}

Entities::~Entities()
{
}

int		Entities::getType()
{
	return (type);
}

int		Entities::getId()
{
	return (id);
}

const std::string&	Entities::getName()
{
	return (name);
}


void	Entities::sId(int _id)
{
	this->id = _id;
}


float Entities::getTMPx()
{
	return this->tmp_x;
}

float Entities::getTMPy()
{
	return this->tmp_y;
}

void	Entities::sTMPx(float x)
{
	this->tmp_x = x;
}

void	Entities::sTMPy(float y)
{
	this->tmp_y = y;
}