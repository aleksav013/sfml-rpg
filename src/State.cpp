#include"includes/Global.hpp"
#include"includes/State.hpp"

#include"includes/Game.hpp"
#include<iostream>
State::State()
{
    prozor.create(sf::VideoMode::getFullscreenModes()[0],"RPG igra");
    prozor.setFramerateLimit(60);
    visina=prozor.getSize().y;
    sirina=prozor.getSize().x;
}
void State::events()
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
		std::cout<<"Nova velicina prozora je:"<<prozor.getSize().x<<'x'<<prozor.getSize().y<<std::endl;
		ischanged=1;
		visina=prozor.getSize().y;
		sirina=prozor.getSize().x;
		prozor.setView(sf::View(sf::FloatRect(0,0,sirina,visina)));
		break;
	    case sf::Event::EventType::KeyPressed:
		keyboard();
		break;
	    default:
		break;
	}
    }
}
void State::keyboard()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
	pause=1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
	pause=0;
	ischanged=1;
    }
}
void State::loop()
{
    Game *igra=new Game(&prozor);
    while(prozor.isOpen())
    {
	events();
	igra->loop(ischanged,pause);
	if(ischanged) ischanged=0;
    }
}
