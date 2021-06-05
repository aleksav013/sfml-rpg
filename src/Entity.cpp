#include"includes/Global.hpp"
#include"includes/Entity.hpp"

Entity::Entity(sf::Vector2f pozicija, sf::Vector2f velicina,sf::Color boja)
{
    telo.setSize(velicina);
    telo.setFillColor(boja);
    telo.setOrigin(sf::Vector2f(telo.getSize().x/2,telo.getSize().y/2));
    x=pozicija.x;
    y=pozicija.y; 
}
void Entity::respawn(int sirina,int visina)
{
    if(!ziv)
    {
	x=Global::rng()%sirina;
	y=Global::rng()%visina;
	ziv=1;
    }
}
