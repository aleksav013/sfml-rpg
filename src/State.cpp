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
    prozor=std::make_shared<sf::RenderWindow>(sf::VideoMode::getFullscreenModes()[0],"RPG igra",sf::Style::Default);
    prozor->setVerticalSyncEnabled(true);
    visina=prozor->getSize().y;
    sirina=prozor->getSize().x;
}
void State::initassets()
{
    font["default"]=std::make_shared<sf::Font>();
    tex["neprijatelj"]=std::make_shared<sf::Texture>();
    tex["health"]=std::make_shared<sf::Texture>();
    tex["clear"]=std::make_shared<sf::Texture>();
    tex["vampiric"]=std::make_shared<sf::Texture>();
    //tex["djule"]=std::make_shared<sf::Texture>();
    font["default"]->loadFromFile("assets/fonts/LiberationMono-Regular.ttf");
    tex["health"]->loadFromFile("assets/images/healing.png");
    tex["neprijatelj"]->loadFromFile("assets/images/nep.png");
    tex["clear"]->loadFromFile("assets/images/clear.png");
    tex["vampiric"]->loadFromFile("assets/images/vampiric.png");
    //tex["djule"]->loadFromFile("assets/images/djule.png");
}
void State::events() {
    sf::Event evnt;
    while(prozor->pollEvent(evnt))
    {
	switch(evnt.type)
	{
	    case sf::Event::EventType::Closed:
		prozor->close();
		break;
	    case sf::Event::EventType::Resized:
		ischanged=1;
		visina=prozor->getSize().y;
		sirina=prozor->getSize().x;
		prozor->setView(sf::View(sf::FloatRect(0,0,sirina,visina)));
		std::cout<<"Nova velicina prozora je:"<<sirina<<'x'<<visina<<std::endl;
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
	prozor->close();
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

    pausetext.setFont(*font["default"]);
    pausetext.setString("Pauza\nPritisnite Esc da nastavite igru");
    pausetext.setCharacterSize(24);
    pausetext.setStyle(sf::Text::Bold);
    pausetext.setFillColor(sf::Color::White);
    pausetext.setOrigin(pausetext.getGlobalBounds().width/2.0,pausetext.getGlobalBounds().height/2.0);

    krajtext.setFont(*font["default"]);
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
    std::unique_ptr<Game> igra=std::make_unique<Game>(prozor,font,tex);
    while(prozor->isOpen())
    {
	events();
	kraj=igra->gameover();
	igra->loop(ischanged,pause||kraj);
	if(ischanged) updateui();

	igra->draw();
	if(kraj)
	{
	    prozor->draw(podloga);
	    prozor->draw(krajtext);
	    if(newgame)
	    {
		igra=std::make_unique<Game>(prozor,font,tex);
	    }
	}
	if(pause)
	{
	    prozor->draw(podloga);
	    prozor->draw(pausetext);
	}
	prozor->display();
	prozor->clear();

	ischanged=0;
	newgame=0;
    }
}
