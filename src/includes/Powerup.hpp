#ifndef POWRUP_H
#define POWERUP_H

#include"Entity.hpp"
class Powerup:public Entity
{
    public:
	static float time;
	int type;
	Powerup():Entity() {}
	Powerup(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja,int vrsta);
	void respawn(int sirina,int visina,int vrsta);
};

#endif
