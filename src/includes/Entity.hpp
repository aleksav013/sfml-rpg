#ifndef ENTITY_H
#define ENTITY_H

#include<SFML/Graphics.hpp>
class Entity
{
    public:
	bool ziv=1;
	float x,y;
	sf::RectangleShape telo;
	Entity() {} Entity(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
	void respawn(int sirina,int visina);
};

#endif
