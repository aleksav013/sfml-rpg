#include"includes/Global.hpp"
#include"includes/Game.hpp"

#include<iostream>
void Game::initshapes()
{
    krug.setRadius(igrac.stomprad);
    krug.setFillColor(sf::Color::Black);
    krug.setOutlineThickness(10);
    krug.setOutlineColor(sf::Color::White);
    krug.setOrigin(krug.getRadius(),krug.getRadius());

    health.setSize(sf::Vector2f(sirina/3.0,50.0));
    health.setFillColor(sf::Color::Red);
    healthblank.setSize(sf::Vector2f(sirina/3.0,50.0));
    healthblank.setFillColor(sf::Color::White);

    stomp.setSize(sf::Vector2f(sirina/3.0,50.0));
    stomp.setFillColor(sf::Color::Blue);
    stomp.setPosition(0,50);
    stompblank.setSize(sf::Vector2f(sirina/3.0,50.0));
    stompblank.setFillColor(sf::Color::White);
    stompblank.setPosition(0,50);
}
void Game::initui()
{
    if(!font.loadFromFile("../assets/fonts/LiberationMono-Regular.ttf"))
    {
	std::cerr<<"Font not found\n";
    }
    healthtext.setFont(font);
    healthtext.setString("Health");
    healthtext.setCharacterSize(24);
    healthtext.setFillColor(sf::Color::Black);
    stomptext.setFont(font);
    stomptext.setString("Stomp");
    stomptext.setCharacterSize(24);
    stomptext.setPosition(0,50);
    stomptext.setFillColor(sf::Color::Black);

    fps.setFont(font);
    fps.setCharacterSize(24);
    fps.setFillColor(sf::Color::White);
    fps.setPosition(sirina*5.0/6,0);
    score.setFont(font);
    score.setCharacterSize(24);
    score.setFillColor(sf::Color::White);
    score.setPosition(sirina*5.0/6,50);
}
void Game::inittex()
{
    if(!healthtex.loadFromFile("../assets/images/healing.png"))
    {
	std::cerr<<"Texture not found\n";
    }
    if(!neprijateljtex.loadFromFile("../assets/images/nep.png"))
    {
	std::cerr<<"Texture not found\n";
    }
    for(size_t i=0;i<pow.size();i++) pow.at(i).telo.setTexture(&healthtex);
    for(size_t i=0;i<nep1.size();i++) nep1.at(i).telo.setTexture(&neprijateljtex);
    for(size_t i=0;i<nep2.size();i++) nep2.at(i).telo.setTexture(&neprijateljtex);
    for(size_t i=0;i<nep3.size();i++) nep3.at(i).telo.setTexture(&neprijateljtex);
}
void Game::initent()
{
    igrac = Player(sf::Vector2f(sirina/2.0,visina/2.0),sf::Vector2f(100.0f,100.0f),sf::Color::White);
    for(size_t i=0;i<20;i++) nep1.push_back(Enemy1(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::Red));
    for(size_t i=0;i<7;i++) nep2.push_back(Enemy2(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::Cyan));//(253,106,2)));
    for(size_t i=0;i<4;i++) nep3.push_back(Enemy3(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::Yellow));
    pow.push_back(Powerup(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::White));
}
void Game::updatewin()
{
    visina=prozor->getSize().y;
    sirina=prozor->getSize().x;
    healthblank.setSize(sf::Vector2f(sirina/3.0,50.0));
    stompblank.setSize(sf::Vector2f(sirina/3.0,50.0));
    fps.setPosition(sirina*5.0/6,0);
    score.setPosition(sirina*5.0/6,50);
    updateui();
}
Game::Game(sf::RenderWindow *glprozor)
{
    prozor=glprozor;
    initui();
    updatewin();
    initent();
    initshapes();
    inittex();
}
bool Game::gameover()
{
    if(igrac.health<=0)
    {
	prozor->close();
	std::cout<<"\n\nGame over. Wanna try again?\n";
	return 1;
    }
    return 0;
}
void Game::updatedt()
{
    dt=sat.restart().asMicroseconds()/1000000.0;
}
void Game::updateui()
{
    health.setSize(sf::Vector2f(sirina*igrac.health/300.0,50.0));
    stomp.setSize(sf::Vector2f(sirina*(5-igrac.stomptime)/15.0,50.0));
    fps.setString("fps: "+std::to_string((int)(1/dt)));
    score.setString("xp: "+std::to_string(igrac.xp));
}
void Game::stompmain()
{
    igrac.stomptime=5;
    krug.setPosition(igrac.x,igrac.y);
    for(size_t i=0;i<nep1.size();i++) if(nep1.at(i).ziv)
    {
	if(seseku(nep1.at(i).telo,krug))
	{
	    igrac.xp+=5;
	    nep1.at(i).ziv=0;
	}
    }
    for(size_t i=0;i<nep2.size();i++) if(nep2.at(i).ziv)
    {
	if(seseku(nep2.at(i).telo,krug))
	{
	    igrac.xp+=10;
	    nep2.at(i).ziv=0;
	}
    }
    for(size_t i=0;i<nep3.size();i++) if(nep3.at(i).ziv)
    {
	if(seseku(nep3.at(i).telo,krug))
	{
	    igrac.xp+=20;
	    nep3.at(i).ziv=0;
	}
    }
}
void Game::keyboard()
{
    float dist=500.0*dt;
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::W)||sf::Keyboard::isKeyPressed(sf::Keyboard::Up))&&igrac.y>0) igrac.y-=dist;
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::Left))&&igrac.x>0) igrac.x-=dist;
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::S)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down))&&igrac.y<visina) igrac.y+=dist;
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))&&igrac.x<sirina) igrac.x+=dist;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) if(igrac.stomptime<=0) stompmain();
}
void Game::draw()
{
    prozor->clear();
    if(igrac.stomptime>4.6) prozor->draw(krug);
    prozor->draw(igrac.telo);
    for(size_t i=0;i<nep1.size();i++) if(nep1.at(i).ziv) prozor->draw(nep1.at(i).telo);
    for(size_t i=0;i<nep2.size();i++) if(nep2.at(i).ziv) prozor->draw(nep2.at(i).telo);
    for(size_t i=0;i<nep3.size();i++) if(nep3.at(i).ziv) prozor->draw(nep3.at(i).telo);
    for(size_t i=0;i<pow.size();i++) if(pow.at(i).ziv) prozor->draw(pow.at(i).telo);

    prozor->draw(healthblank);
    prozor->draw(health);
    prozor->draw(healthtext);
    prozor->draw(stompblank);
    prozor->draw(stomp);
    prozor->draw(stomptext);
    prozor->draw(fps);
    prozor->draw(score);

    prozor->display();
}
void Game::position()
{
    igrac.telo.setPosition(igrac.x,igrac.y);
    for(size_t i=0;i<nep1.size();i++) if(nep1.at(i).ziv)
    {
	nep1.at(i).izracunajbrzinu(igrac.x,igrac.y);
	nep1.at(i).izracunajpoz(dt);
	nep1.at(i).telo.setPosition(nep1.at(i).x,nep1.at(i).y);
    }
    for(size_t i=0;i<nep2.size();i++) if(nep2.at(i).ziv)
    {
	nep2.at(i).izracunajbrzinu(igrac.x,igrac.y,dt);
	nep2.at(i).izracunajpoz(igrac.x,igrac.y,dt);
	nep2.at(i).telo.setPosition(nep2.at(i).x,nep2.at(i).y);
    }
    for(size_t i=0;i<nep3.size();i++) if(nep3.at(i).ziv)
    {
	nep3.at(i).izracunajbrzinu(sirina,visina);
	nep3.at(i).izracunajpoz(dt);
	nep3.at(i).telo.setPosition(nep3.at(i).x,nep3.at(i).y);
    }
    for(size_t i=0;i<pow.size();i++) if(pow.at(i).ziv)
    {
	pow.at(i).telo.setPosition(pow.at(i).x,pow.at(i).y);
    }
}
void Game::checkcollision()
{
    for(size_t i=0;i<nep1.size();i++) if(nep1.at(i).ziv)
    {
	if(seseku(nep1.at(i).telo,igrac.telo))
	{
	    nep1.at(i).ziv=0;
	    igrac.health-=Global::rng()%4+1; // 1-4 dmg
	}
    }
    for(size_t i=0;i<nep2.size();i++) if(nep2.at(i).ziv)
    {
	if(seseku(nep2.at(i).telo,igrac.telo))
	{
	    nep2.at(i).ziv=0;
	    igrac.health-=Global::rng()%8+1; // 1-8 dmg
	}
    }
    for(size_t i=0;i<nep3.size();i++) if(nep3.at(i).ziv)
    {
	if(seseku(nep3.at(i).telo,igrac.telo))
	{
	    nep3.at(i).ziv=0;
	    igrac.health-=Global::rng()%12+1; // 1-12 dmg
	}
    }
    for(size_t i=0;i<pow.size();i++) if(pow.at(i).ziv)
    {
	if(seseku(pow.at(i).telo,igrac.telo))
	{
	    pow.at(i).ziv=0;
	    igrac.health+=Global::rng()%20+21; // 20-40 heal
	}
    }
}
void Game::respawn()
{
    Enemy1::time-=dt;
    Enemy2::time-=dt;
    Enemy3::time-=dt;
    Powerup::time-=dt;

    if(Enemy1::time<0)
    {
	Enemy1::time=8;
	for(size_t i=0;i<nep1.size();i++) nep1.at(i).respawn(sirina,visina);
    }
    if(Enemy2::time<0)
    {
	Enemy2::time=14;
	for(size_t i=0;i<nep2.size();i++) nep2.at(i).respawn(sirina,visina);
    }
    if(Enemy3::time<0)
    {
	Enemy3::time=10;
	for(size_t i=0;i<nep3.size();i++) nep3.at(i).respawn(sirina,visina);
    }
    if(Powerup::time<0)
    {
	Powerup::time=20;
	for(size_t i=0;i<pow.size();i++) pow.at(i).respawn(sirina,visina);
    }
}
void Game::run()
{
    if(gameover()) return;

    updateui();
    igrac.updatest(dt);

    respawn();
    position();
    checkcollision();
}
void Game::loop(bool ischanged,bool pause)
{
    if(ischanged) updatewin();
    if(!pause)
    {
	keyboard();
	run();
    }
    updatedt();
    draw();
}
