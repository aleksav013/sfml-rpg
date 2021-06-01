#ifndef ENEMY1_H
#define ENEMY1_H

#include"Entity.hpp"
class Enemy1:public Entity
{
    private:
	float vx,vy;
    public:
	static float time;
	Enemy1():Entity() {}
	Enemy1(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
	void izracunajbrzinu(float igracx,float igracy);
	void izracunajpoz(float dt);
};

#endif
