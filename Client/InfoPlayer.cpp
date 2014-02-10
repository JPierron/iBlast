#include <sstream>
#include "InfoPlayer.h"

InfoPlayer::InfoPlayer(std::string _name, int _lives, int _point)
{
    std::ostringstream nb;
    lives = _lives;
    point = _point;
    nb << point;
    w_type[0] = false;
    w_type[1] = false;
    w_type[2] = false;
    w_type[3] = false;
    Image.Create(_WIDTH, 90, sf::Color(CONT, CONT, CONT));
    sprite.SetImage(Image);
    sprite.SetPosition(0.0, _EIGHT-90);
    playername.SetText(_name);
    playername.SetPosition(10, 515);
    speed_bonus.SetText("Speed Shot");
    speed_bonus.SetPosition(530, 515);
    speed_bonus.SetColor(sf::Color(0, 0, 200));
    split_bonus.SetText("Shot Splited");
    split_bonus.SetPosition(530, 555);
    split_bonus.SetColor(sf::Color(0, 200, 0));
    speed_charge_bonus.SetText("X2");
    speed_charge_bonus.SetSize(30);
    speed_charge_bonus.SetPosition(400, 540);
    speed_charge_bonus.SetColor(sf::Color(200, 200, 0));
    score.SetText("Score : " + nb.str());
    score.SetPosition(200, 521);
    score.SetSize(22);
    score.SetColor(sf::Color(200, 200, 200));
    if (life.LoadFromFile("Ressources/life.png"))
    {
        life.CreateMaskFromColor(sf::Color(255, 255, 255));
        life1.SetImage(life);
        life1.Resize(50, 35);
        life1.SetPosition(10 + (SPACE*0), 560);
        life2.SetImage(life);
        life2.Resize(50, 35);
        life2.SetPosition(10 + (SPACE*1), 560);
        life3.SetImage(life);
        life3.Resize(50, 35);
        life3.SetPosition(10 + (SPACE*2), 560);
        life4.SetImage(life);
        life4.Resize(50, 35);
        life4.SetPosition(10 + (SPACE*3), 560);
        life5.SetImage(life);
        life5.Resize(50, 35);
        life5.SetPosition(10 + (SPACE*4), 560);
    }
    if (charge.LoadFromFile("Ressources/chargeshot.png"))
    {
        _charge.SetImage(charge);
        _charge.Resize(200, 20);
        _charge.SetPosition(80 + (SPACE*4), 570);
    }
    clockshot.Reset();
    this->shotTimer1 = 0.0f;
    this->shotTimer2 = 0.0f;
}

void    InfoPlayer::playHUD(Plat& _cli, Gui& mainGui)
{
    this->lives = _cli.getLife();
    this->point = _cli.getPts();
    for (int i = 0; i < 4 ; i++)
	{
//		this->w_type[i] = _cli.getWtype(i);
	}
	std::ostringstream nb;
    nb << this->point;
    mainGui.Draw(this->sprite);
    mainGui.Draw(this->playername);
    this->score.SetText("Score : " + nb.str());
    mainGui.Draw(this->score);
    switch (lives)
    {
    case 1:
        mainGui.Draw(this->life1);
        break;
    case 2:
        mainGui.Draw(this->life1);
        mainGui.Draw(this->life2);
        break;
    case 3:
        mainGui.Draw(this->life1);
        mainGui.Draw(this->life2);
        mainGui.Draw(this->life3);
        break;
    case 4:
        mainGui.Draw(this->life1);
        mainGui.Draw(this->life2);
        mainGui.Draw(this->life3);
        mainGui.Draw(this->life4);
        break;
    case 5:
        mainGui.Draw(this->life1);
        mainGui.Draw(this->life2);
        mainGui.Draw(this->life3);
        mainGui.Draw(this->life4);
        mainGui.Draw(this->life5);
        break;
    }
    mainGui.Draw(this->_charge);
    if (this->w_type[0])
        mainGui.Draw(this->speed_bonus);
    if (this->w_type[1])
        mainGui.Draw(this->split_bonus);
    if (this->w_type[2])
        mainGui.Draw(this->speed_charge_bonus);
    if(mainGui.GetInput().IsKeyDown(sf::Key::Space)) // a garder et remplacer la touche Space par la touche de charge
    {
        this->shotTimer2 = this->clockshot.GetElapsedTime();
        this->shotTimer1 = this->shotTimer2 * TIMER;
        if (this->w_type[2])
            this->shotTimer1 *= 2;
        if (this->shotTimer1 > 164)
            this->shotTimer1 = 164;
        mainGui.Draw(sf::Shape::Rectangle(339, 576, 339 + this->shotTimer1, 585, sf::Color(255, 0, 0)));
    }
    else
        this->clockshot.Reset();
}

void    InfoPlayer::setLives(int _lives)
{
    this->lives = _lives;
}

void    InfoPlayer::setPoint(int _point)
{
    this->point = _point;
}

void    InfoPlayer::setWtype(int key, bool iset)
{
    this->w_type[key] = iset;
}

int     InfoPlayer::getLives()
{
    return(this->lives);
}

int     InfoPlayer::getPoint()
{
    return(this->point);
}

bool    InfoPlayer::getWtype(int key)
{
    return(this->w_type[key]);
}

InfoPlayer::~InfoPlayer()
{
}