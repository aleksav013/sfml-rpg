#include"includes/Global.hpp"
#include"includes/Powerup.hpp"

float Powerup::time=20;
Powerup::Powerup(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja,int vrsta):Entity(pozicija,velicina,boja)
{
    type=vrsta;
}
void Powerup::respawn(int sirina,int visina,int vrsta)
{
    Entity::respawn(sirina,visina);
    type=vrsta;
}
