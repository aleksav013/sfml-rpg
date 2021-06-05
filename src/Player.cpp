#include"includes/Global.hpp"
#include"includes/Player.hpp"

Player::Player(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja)
{
    health=100;
    stomptime=0;
    vampirictime=0;
    xp=0;

    krug.setRadius(stomprad);
    krug.setFillColor(sf::Color::Black);
    krug.setOutlineThickness(10);
    krug.setOutlineColor(sf::Color::White);
    krug.setOrigin(krug.getRadius(),krug.getRadius());
}
void Player::updatest(float dt)
{
    if(stomptime>0) stomptime-=dt;
    else stomptime=0;
}
void Player::updatevt(float dt)
{
    if(vampirictime>0) vampirictime-=dt;
    else vampirictime=0;
}
