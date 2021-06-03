#include"includes/Global.hpp"
#include"includes/State.hpp"

#include"includes/Game.hpp"
#include<iostream>
State::State()
{
    initwin();
    initassets();
    initui();
}
void State::initwin()
{
    prozor.create(sf::VideoMode::getFullscreenModes()[0],"RPG igra");
    prozor.setFramerateLimit(60);
    visina=prozor.getSize().y;
    sirina=prozor.getSize().x;
}
void State::initassets()
{
    if(!font.loadFromFile("assets/fonts/LiberationMono-Regular.ttf"))
    {
	std::cerr<<"Font not found\n";
    }
    if(!healthtex.loadFromFile("assets/images/healing.png"))
    {
	std::cerr<<"Texture not found\n";
    }
    if(!neprijateljtex.loadFromFile("assets/images/nep.png"))
    {
	std::cerr<<"Texture not found\n";
    }
}
void State::events() {
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)&&!kraj)
    {
	pause=1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
	pause=0;
	ischanged=1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
    {
	newgame=1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
    {
	prozor.close();
    }
}
void State::initui()
{
    podloga.setPosition(sirina/2.0,visina/2.0);
    podloga.setFillColor(sf::Color::Black);
    podloga.setOutlineColor(sf::Color::White);
    podloga.setOutlineThickness(5);
    podloga.setSize(sf::Vector2f(600.0f,120.0f));
    podloga.setOrigin(podloga.getSize().x/2.0,podloga.getSize().y/2.0);

    pausetext.setFont(font);
    pausetext.setString("Pauza\nPritisnite Esc da nastavite igru");
    pausetext.setCharacterSize(24);
    pausetext.setStyle(sf::Text::Bold);
    pausetext.setFillColor(sf::Color::White);
    pausetext.setOrigin(pausetext.getGlobalBounds().width/2.0,pausetext.getGlobalBounds().height/2.0);

    krajtext.setFont(font);
    krajtext.setString("Kraj igre\nPritisnite Y da zapocnete novu igru");
    krajtext.setCharacterSize(24);
    krajtext.setStyle(sf::Text::Bold);
    krajtext.setFillColor(sf::Color::White);
    krajtext.setOrigin(krajtext.getGlobalBounds().width/2.0,krajtext.getGlobalBounds().height/2.0);

    updateui();
}
void State::updateui()
{
    pausetext.setPosition(sirina/2.0,visina/2.0);
    krajtext.setPosition(sirina/2.0,visina/2.0);
    podloga.setPosition(sirina/2.0,visina/2.0);
}
void State::loop()
{
    Game *igra=new Game(&prozor,font,&healthtex,&neprijateljtex);
    while(prozor.isOpen())
    {
	events();
	kraj=igra->gameover();
	igra->loop(ischanged,pause||kraj);
	if(ischanged) updateui();

	prozor.clear();
	igra->draw();
	if(kraj)
	{
	    prozor.draw(podloga);
	    prozor.draw(krajtext);
	    if(newgame) igra=new Game(&prozor,font,&healthtex,&neprijateljtex);
	}
	if(pause)
	{
	    prozor.draw(podloga);
	    prozor.draw(pausetext);
	}
	prozor.display();

	ischanged=0;
	newgame=0;
    }
}
