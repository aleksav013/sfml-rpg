#include"includes/Global.hpp"
#include"includes/Game.hpp"

void Game::initshapes()
{
    health.setSize(sf::Vector2f(sirina/3.0,50.0));
    health.setFillColor(sf::Color(255,0,0,200));
    healthblank.setSize(sf::Vector2f(sirina/3.0,50.0));
    healthblank.setFillColor(sf::Color(255,255,255,200));

    stomp.setSize(sf::Vector2f(sirina/3.0,50.0));
    stomp.setFillColor(sf::Color(0,0,255,200));
    stomp.setPosition(0,50);
    stompblank.setSize(sf::Vector2f(sirina/3.0,50.0));
    stompblank.setFillColor(sf::Color(255,255,255,200));
    stompblank.setPosition(0,50);

    vampiric.setSize(sf::Vector2f(sirina/3.0,50.0));
    vampiric.setFillColor(sf::Color(170,10,10,200));
    vampiric.setPosition(0,100);
    vampiricblank.setSize(sf::Vector2f(sirina/3.0,50.0));
    vampiricblank.setFillColor(sf::Color(255,255,255,200));
    vampiricblank.setPosition(0,100);
}
void Game::initui()
{
    healthtext.setFont(*font["default"]);
    healthtext.setString("Health");
    healthtext.setCharacterSize(24);
    healthtext.setFillColor(sf::Color::Black);
    stomptext.setFont(*font["default"]);
    stomptext.setString("Stomp");
    stomptext.setCharacterSize(24);
    stomptext.setPosition(0,50);
    stomptext.setFillColor(sf::Color::Black);
    vampirictext.setFont(*font["default"]);
    vampirictext.setString("Vampiric");
    vampirictext.setCharacterSize(24);
    vampirictext.setPosition(0,100);
    vampirictext.setFillColor(sf::Color::Black);

    fps.setFont(*font["default"]);
    fps.setCharacterSize(24);
    fps.setFillColor(sf::Color::White);
    fps.setPosition(sirina*5.0/6,0);
    score.setFont(*font["default"]);
    score.setCharacterSize(24);
    score.setFillColor(sf::Color::White);
    score.setPosition(sirina*5.0/6,50);
}
void Game::pwptex()
{
    for(size_t i=0;i<pow.size();i++) switch(pow.at(i).type)
    {
	case 1:
	    pow.at(i).telo.setTexture(tex["health"].get());
	    break;
	case 2:
	    pow.at(i).telo.setTexture(tex["clear"].get());
	    break;
	case 3:
	    pow.at(i).telo.setTexture(tex["vampiric"].get());
	    break;
	default:
	    break;
    }
}
void Game::inittex()
{
    for(size_t i=0;i<nep1.size();i++) nep1.at(i).telo.setTexture(tex["neprijatelj"].get());
    for(size_t i=0;i<nep2.size();i++) nep2.at(i).telo.setTexture(tex["neprijatelj"].get());
    for(size_t i=0;i<nep3.size();i++) nep3.at(i).telo.setTexture(tex["neprijatelj"].get());
    pwptex();
}
void Game::initent()
{
    igrac = Player(sf::Vector2f(sirina/2.0,visina/2.0),sf::Vector2f(100.0f,100.0f),sf::Color::White);
    for(size_t i=0;i<20;i++) nep1.emplace_back(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::Red);
    for(size_t i=0;i<7;i++) nep2.emplace_back(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::Cyan);
    for(size_t i=0;i<4;i++) nep3.emplace_back(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::Yellow);
    pow.emplace_back(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::White,Global::rng()%3+1);
}
void Game::updatewin()
{
    visina=prozor->getSize().y;
    sirina=prozor->getSize().x;
    healthblank.setSize(sf::Vector2f(sirina/3.0,50.0));
    stompblank.setSize(sf::Vector2f(sirina/3.0,50.0));
    fps.setPosition(sirina*5.0/6,0);
    score.setPosition(sirina*5.0/6,50);
}
Game::Game(std::shared_ptr<sf::RenderWindow> mainprozor,std::map<std::string,std::shared_ptr<sf::Font>> mainfont,std::map<std::string,std::shared_ptr<sf::Texture>> maintex)
{
    prozor=mainprozor;
    font=mainfont;
    tex=maintex;

    updatewin();
    initshapes();
    initent();
    inittex();
    updatedt();
    initui();
    updateui();
}
bool Game::gameover()
{
    if(igrac.health<=0) return 1;
    return 0;
}
void Game::updatedt()
{
    dt=sat.restart().asMicroseconds()/1000000.0;
    if(dt>0.5) dt=0;
}
void Game::updateui()
{
    health.setSize(sf::Vector2f(sirina*igrac.health/300.0,50.0));
    if(igrac.health>=100) healthblank.setSize(health.getSize());
    else healthblank.setSize(sf::Vector2f(sirina/3.0,50.0));
    stomp.setSize(sf::Vector2f(sirina*(5-igrac.stomptime)/15.0,50.0));
    vampiric.setSize(sf::Vector2f(sirina*(igrac.vampirictime)/36.0,50.0));
    fps.setString("fps: "+std::to_string((int)(1/dt)));
    score.setString("xp: "+std::to_string(igrac.xp));
}
void Game::stompmain()
{
    igrac.stomptime=5;
    igrac.krug.setPosition(igrac.x,igrac.y);
    for(size_t i=0;i<nep1.size();i++) if(nep1.at(i).ziv)
    {
	if(seseku(nep1.at(i).telo,igrac.krug))
	{
	    igrac.xp+=5;
	    nep1.at(i).ziv=0;
	    if(igrac.vampirictime>0) igrac.health+=5;
	}
    }
    for(size_t i=0;i<nep2.size();i++) if(nep2.at(i).ziv)
    {
	if(seseku(nep2.at(i).telo,igrac.krug))
	{
	    igrac.xp+=10;
	    nep2.at(i).ziv=0;
	    if(igrac.vampirictime>0) igrac.health+=10;
	}
    }
    for(size_t i=0;i<nep3.size();i++) if(nep3.at(i).ziv)
    {
	if(seseku(nep3.at(i).telo,igrac.krug))
	{
	    igrac.xp+=20;
	    nep3.at(i).ziv=0;
	    if(igrac.vampirictime>0) igrac.health+=20;
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
    if(igrac.stomptime>4.6)
    {
	if(igrac.vampirictime>0) igrac.krug.setOutlineColor(sf::Color::Red);
	else igrac.krug.setOutlineColor(sf::Color::White);
	prozor->draw(igrac.krug);
    }
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
    if(igrac.vampirictime>0)
    {
	prozor->draw(vampiricblank);
	prozor->draw(vampiric);
	prozor->draw(vampirictext);
    }
    prozor->draw(fps);
    prozor->draw(score);
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
	    igrac.health-=Global::rng()%4+1;
	}
    }
    for(size_t i=0;i<nep2.size();i++) if(nep2.at(i).ziv)
    {
	if(seseku(nep2.at(i).telo,igrac.telo))
	{
	    nep2.at(i).ziv=0;
	    igrac.health-=Global::rng()%8+1;
	}
    }
    for(size_t i=0;i<nep3.size();i++) if(nep3.at(i).ziv)
    {
	if(seseku(nep3.at(i).telo,igrac.telo))
	{
	    nep3.at(i).ziv=0;
	    igrac.health-=Global::rng()%12+1;
	}
    }
    for(size_t i=0;i<pow.size();i++) if(pow.at(i).ziv)
    {
	if(seseku(pow.at(i).telo,igrac.telo))
	{
	    pow.at(i).ziv=0;
	    switch(pow.at(i).type)
	    {
		case 1:
		    //health
		    igrac.health+=Global::rng()%20+21;
		    break;
		case 2:
		    //clear
		    for(size_t i=0;i<nep1.size();i++) if(nep1.at(i).ziv)
		    {
			nep1.at(i).ziv=0;
			igrac.xp+=5;
		    }
		    for(size_t i=0;i<nep2.size();i++) if(nep2.at(i).ziv)
		    {
			nep2.at(i).ziv=0;
			igrac.xp+=10;
		    }
		    for(size_t i=0;i<nep3.size();i++) if(nep3.at(i).ziv)
		    {
			nep3.at(i).ziv=0;
			igrac.xp+=20;
		    }
		    break;
		case 3:
		    //vampiric
		    igrac.vampirictime=12;
		    break;
		default:
		    break;
	    }
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
	for(size_t i=0;i<pow.size();i++) pow.at(i).respawn(sirina,visina,Global::rng()%3+1);
	pwptex();
    }
}
void Game::run()
{
    igrac.updatest(dt);
    igrac.updatevt(dt);
    respawn();
    position();
    checkcollision();
}
void Game::loop(bool ischanged,bool pause)
{
    updatedt();
    if(ischanged)
    {
	updatewin();
	updateui();
    }
    if(!pause)
    {
	keyboard();
	run();
    }
    updateui();
}
