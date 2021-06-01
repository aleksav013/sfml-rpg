#include"includes/Global.hpp"
#include"includes/Enemy3.hpp"
float Enemy3::time=10;
Enemy3::Enemy3(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja)
{
    vx=vy=500.0;
}
void Enemy3::izracunajpoz(float dt)
{
    x+=vx*dt;
    y+=vy*dt;
}
void Enemy3::izracunajbrzinu(int sirina,int visina)
{
    if(x<0||x>sirina) vx=-vx;
    if(y<0||y>visina) vy=-vy;
}
