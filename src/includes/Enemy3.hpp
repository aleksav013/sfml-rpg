#ifndef ENEMY3_H
#define ENEMY3_H

#include"Entity.hpp"
class Enemy3:public Entity
{
    private:
	float vx=0,vy=0;
    public:
	static float time;
	Enemy3():Entity() {}
	Enemy3(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
	void izracunajpoz(float dt);
	void izracunajbrzinu(int sirina,int duzina);
};

#endif
