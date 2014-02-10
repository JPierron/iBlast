#ifndef _INFOPLAYER_H_
#define _INFOPLAYER_H_

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Client.h"
#include "iBlast.h"
#include "Gui.h"

#define _EIGHT   600
#define _WIDTH   800
#define CONT    30
#define SPACE   60
#define TIMER   77.5f
class	Gui;
class   InfoPlayer
{
public:
    InfoPlayer(std::string, int, int);
    ~InfoPlayer();
	void    playHUD(Plat&, Gui&);
    void    setLives(int);
    void    setPoint(int);
    void    setWtype(int, bool);
    int     getLives();
    int     getPoint();
    bool    getWtype(int);

private:
sf::RenderWindow App;
sf::Sprite sprite;
sf::Image   Image;
int         lives;
int         point;
bool        w_type[3];
sf::String  playername;
sf::String  score;
sf::Image   life;
sf::Sprite  life1;
sf::Sprite  life2;
sf::Sprite  life3;
sf::Sprite  life4;
sf::Sprite  life5;
sf::Image   charge;
sf::Sprite  _charge;
sf::String  speed_bonus;
sf::String  split_bonus;
sf::String  speed_charge_bonus;
sf::Clock   clockshot;
float       shotTimer1;
float       shotTimer2;
};

#endif