#include"includes/Global.hpp"
#include"includes/Player.hpp"
Player::Player(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja)
{
    health=100;
    stomptime=0;
    xp=0;
}
void Player::updatest(float dt)
{
    if(stomptime>0) stomptime-=dt;
    else stomptime=0;
}
