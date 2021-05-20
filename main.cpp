#include<iostream>
#include<SFML/Graphics.hpp>
class Player
{
    public:
	float x,y;
	sf::RectangleShape telo;
	Player();
};
Player::Player()
{
    telo.setSize(sf::Vector2f(100.0f,100.0f));
    telo.setOrigin(sf::Vector2f(telo.getSize().x/2,telo.getSize().y/2));
    x=y=0;
}
class Game
{
    Player igrac;
    sf::RenderWindow prozor;
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
    igrac.x=(float)prozor.getSize().x/2;
    igrac.y=(float)prozor.getSize().y/2;
}
void Game::keyboard()
{
    float dist=10.0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) igrac.y-=dist;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) igrac.x-=dist;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) igrac.y+=dist;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) igrac.x+=dist;
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
		std::cout<<"Nova velicina prozora je:"<<prozor.getSize().x<<' '<<prozor.getSize().x<<std::endl;
		break;
	}
    }
    keyboard();
}
void Game::draw()
{
    prozor.clear();
    prozor.draw(igrac.telo);
    prozor.display();
}
void Game::run()
{
    igrac.telo.setPosition(igrac.x,igrac.y);
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
