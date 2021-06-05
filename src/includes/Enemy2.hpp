#ifndef ENEMY2_H
#define ENEMY2_H

#include"Entity.hpp"
class Enemy2:public Entity
{
    private:
	float vx=0,vy=0;
    public:
	static float time;
	Enemy2():Entity() {}
	Enemy2(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
	void izracunajbrzinu(float igracx,float igracy,float dt);
	void izracunajpoz(float igracx,float igracy,float dt);
};

#endif
