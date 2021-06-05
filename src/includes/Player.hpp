#ifndef PLAYER_H
#define PLAYER_H

#include"Entity.hpp"
class Player:public Entity
{
    public:
	int health,xp;
	int stomprad=270;
	float stomptime,vampirictime;

	sf::CircleShape krug;

	Player():Entity() {}
	Player(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
	void updatest(float dt);
	void updatevt(float dt);
};

#endif
