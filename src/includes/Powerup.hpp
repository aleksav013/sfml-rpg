#ifndef POWRUP_H
#define POWERUP_H

#include"Entity.hpp"
class Powerup:public Entity
{
    public:
	static float time;
	Powerup():Entity() {}
	Powerup(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
};

#endif
