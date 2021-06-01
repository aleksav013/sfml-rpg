#include"includes/Global.hpp"
#include"includes/Enemy2.hpp"
float Enemy2::time=14;
Enemy2::Enemy2(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja)
{
    vx=vy=0;
}
void Enemy2::izracunajbrzinu(float igracx,float igracy,float dt)
{
    float k=(igracy-y)/(igracx-x);
    float r=200.0*dt;
    float dx=r/std::sqrt(1+k*k);
    if(igracx-x<0) dx=-dx;
    float dy=k*dx;
    vx+=dx;
    vy+=dy;
}
void Enemy2::izracunajpoz(float igracx,float igracy,float dt)
{
    if((x+vx-igracx)*(x+vx-igracx)+(y+vy-igracy)*(y+vy-igracy)<(x-igracx)*(x-igracx)+(y-igracy)*(y-igracy))
    {
	x+=vx*dt*3;
	y+=vy*dt*3;
    }
    else
    {
	x+=vx*dt;
	y+=vy*dt;
    }
}
