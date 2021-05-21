#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include<iostream>
#include<SFML/Graphics.hpp>
#include<random>
std::mt19937 rng(time(0));
const int n=30;
class Entity
{
    public:
	float x,y;
	sf::RectangleShape telo;
	Entity() {}
	Entity(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
};
Entity::Entity(sf::Vector2f pozicija, sf::Vector2f velicina,sf::Color boja)
{
    telo.setSize(velicina);
    telo.setFillColor(boja);
    telo.setOrigin(sf::Vector2f(telo.getSize().x/2,telo.getSize().y/2));
    x=pozicija.x;
    y=pozicija.y;
}
class Enemy:public Entity
{
    public:
	Enemy():Entity() {}
	Enemy(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja) {}
};
class Player:public Entity
{
    int health;
    public:
	Player():Entity() {}
	Player(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja) 
	{
	    health=100;
	}
};
class Game
{
    Player igrac;
    Enemy neprijatelj[n];
    sf::RenderWindow prozor;
    int visina,sirina;
    public:
	Game();
	void loop();
	void events();
	void keyboard();
	void run();
	void draw();
};
Game::Game()
{
    prozor.create(sf::VideoMode(512,512),"RPG igra");
    visina=prozor.getSize().y;
    sirina=prozor.getSize().x;
    prozor.setFramerateLimit(60);
    
    igrac = Player(sf::Vector2f((float)sirina/2,(float)visina/2),sf::Vector2f(100.0f,100.0f),sf::Color::White);
    for(int i=0;i<n;i++) neprijatelj[i] = Enemy(sf::Vector2f(rng()%sirina,rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::Red);

    igrac.x=(float)prozor.getSize().x/2;
    igrac.y=(float)prozor.getSize().y/2;
}
void Game::keyboard()
{
    float dist=10.0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)&&igrac.y>0) igrac.y-=dist;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)&&igrac.x>0) igrac.x-=dist;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)&&igrac.y<visina) igrac.y+=dist;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)&&igrac.x<sirina) igrac.x+=dist;
}
void Game::events()
{
    sf::Event evnt;
    while(prozor.pollEvent(evnt))
    {
	switch(evnt.type)
	{
	    case sf::Event::EventType::Closed:
		prozor.close();
		break;
	    case sf::Event::EventType::Resized:
		visina=prozor.getSize().y;
		sirina=prozor.getSize().x;
		std::cout<<"Nova velicina prozora je:"<<sirina<<'x'<<visina<<std::endl;
		break;
	}
    }
    keyboard();
}
void Game::draw()
{
    prozor.clear();
    prozor.draw(igrac.telo);
    for(int i=0;i<n;i++) prozor.draw(neprijatelj[i].telo);
    prozor.display();
}
void Game::run()
{
    igrac.telo.setPosition(igrac.x,igrac.y);
    for(int i=0;i<n;i++) neprijatelj[i].telo.setPosition(neprijatelj[i].x,neprijatelj[i].y);
}
void Game::loop()
{
    while(prozor.isOpen())
    {
	events();
	run();	
	draw();
    }
}
int main()
{
    Game igra;
    igra.loop();
    return 0;
}
