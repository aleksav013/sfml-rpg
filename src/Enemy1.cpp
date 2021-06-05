#include"includes/Global.hpp"
#include"includes/Enemy1.hpp"

float Enemy1::time=8;
Enemy1::Enemy1(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja) {}
void Enemy1::izracunajbrzinu(float igracx,float igracy)
{
    float k=(igracy-y)/(igracx-x);
    float r=150.0;
    float dx=r/std::sqrt(1+k*k);
    if(igracx-x<0) dx=-dx;
    float dy=k*dx;
    vx=dx;
    vy=dy;
}
void Enemy1::izracunajpoz(float dt)
{
    x+=vx*dt;
    y+=vy*dt;
}
