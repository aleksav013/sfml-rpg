#include<iostream>
#include<SFML/Graphics.hpp>
#include<random>
class Global
{
    public:
	static std::mt19937 rng;
};
std::mt19937 Global::rng = std::mt19937(time(0));
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
class Enemy:public Entity {
    public:
	bool ziv=1;
	Enemy():Entity() {}
	Enemy(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
	void kaigracu(float igracx,float igracy,float dt);
};
Enemy::Enemy(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja) {}
void Enemy::kaigracu(float igracx,float igracy,float dt)
{
    float k=(igracy-y)/(igracx-x);
    float r=100.0*dt;
    float dx=r/std::sqrt(1+k*k);
    if(igracx-x<0) dx=-dx;
    float dy=k*dx;
    x+=dx;
    y+=dy;
}
class Enemy2:public Entity {
    private:
	float vx,vy;
    public:
	bool ziv=1;
	Enemy2():Entity() {}
	Enemy2(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
	void brzina(float igracx,float igracy,float dt);
	void izracunajpoz();
};
Enemy2::Enemy2(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja)
{
    vx=vy=0;
}
void Enemy2::brzina(float igracx,float igracy,float dt)
{
    float k=(igracy-y)/(igracx-x);
    float r=10.0*dt;
    float dx=r/std::sqrt(1+k*k);
    if(igracx-x<0) dx=-dx;
    float dy=k*dx;
    vx+=dx;
    vy+=dy;
}
void Enemy2::izracunajpoz()
{
    x+=vx;
    y+=vy;
}
class Enemy3:public Entity {
    public:
	float vx,vy;
	bool ziv=1;
	Enemy3():Entity() {}
	Enemy3(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
	void izracunajpoz();
};
Enemy3::Enemy3(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja)
{
    vx=vy=10.0;
}
void Enemy3::izracunajpoz()
{
    x+=vx;
    y+=vy;
}
class Player:public Entity
{
    public:
	int health,xp;
	int stomprad=270;
	float stomptime;

	Player():Entity() {}
	Player(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
};
Player::Player(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja)
{
    health=100;
    stomptime=0;
    xp=0;
}
class Game
{
    private:
	float dt;
	sf::Clock sat;
	float time,time2,time3;

	Player igrac;
	std::vector<Enemy> nep;
	std::vector<Enemy2> nep2;
	std::vector<Enemy3> nep3;

	int visina,sirina;
	sf::RenderWindow prozor;
	
	sf::CircleShape krug;
	sf::RectangleShape health,healthblank,stomp,stompblank;

	void events();
	void keyboard();
	void run();
	void draw();
	void stompmain();
	void updateui();
	void updatedt();
    public:
	Game();
	void loop();
};
Game::Game()
{
    time=8;
    time2=14;
    time3=10;
    prozor.create(sf::VideoMode(1024,1024),"RPG igra");
    visina=prozor.getSize().y;
    sirina=prozor.getSize().x;
    prozor.setFramerateLimit(60);
    igrac = Player(sf::Vector2f((float)sirina/2,(float)visina/2),sf::Vector2f(100.0f,100.0f),sf::Color::White);
    for(int i=0;i<20;i++) nep.push_back(Enemy(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::Red));
    for(int i=0;i<10;i++) nep2.push_back(Enemy2(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::Blue));
    for(int i=0;i<5;i++) nep3.push_back(Enemy3(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::Yellow));
    igrac.x=(float)prozor.getSize().x/2;
    igrac.y=(float)prozor.getSize().y/2;

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
    stomp.setPosition(sirina*2.0/3,0);
    stompblank.setSize(sf::Vector2f(sirina/3.0,50.0));
    stompblank.setFillColor(sf::Color::White);
    stompblank.setPosition(sirina*2.0/3,0);
}
void Game::updatedt()
{
    dt=sat.restart().asMicroseconds()/1000000.0;
}
void Game::updateui()
{
    health.setSize(sf::Vector2f(sirina*igrac.health/300.0,50.0));
    stomp.setSize(sf::Vector2f(sirina*(5-igrac.stomptime)/15.0,50.0));
}
void Game::stompmain()
{
    igrac.stomptime=5;
    krug.setPosition(igrac.x,igrac.y);
    for(int i=0;i<nep.size();i++) if(nep[i].ziv)
    {
	if(nep[i].telo.getGlobalBounds().intersects(krug.getGlobalBounds()))
	{
	    igrac.xp+=5;
	    nep[i].ziv=0;
	}
    }
    for(int i=0;i<nep2.size();i++) if(nep2[i].ziv)
    {
	if(nep2[i].telo.getGlobalBounds().intersects(krug.getGlobalBounds()))
	{
	    igrac.xp+=5;
	    nep2[i].ziv=0;
	}
    }
    for(int i=0;i<nep3.size();i++) if(nep3[i].ziv)
    {
	if(nep3[i].telo.getGlobalBounds().intersects(krug.getGlobalBounds()))
	{
	    igrac.xp+=5;
	    nep3[i].ziv=0;
	}
    }
}
void Game::keyboard()
{
    float dist=500.0*dt;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)&&igrac.y>0) igrac.y-=dist;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)&&igrac.x>0) igrac.x-=dist;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)&&igrac.y<visina) igrac.y+=dist;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)&&igrac.x<sirina) igrac.x+=dist;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) if(igrac.stomptime<=0) stompmain();
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
	    default:
		break;
	}
    }
    keyboard();
}
void Game::draw()
{
    prozor.clear();
    if(igrac.stomptime>4.6) prozor.draw(krug);
    prozor.draw(igrac.telo);
    for(int i=0;i<nep.size();i++) if(nep[i].ziv) prozor.draw(nep[i].telo);
    for(int i=0;i<nep2.size();i++) if(nep2[i].ziv) prozor.draw(nep2[i].telo);
    for(int i=0;i<nep3.size();i++) if(nep3[i].ziv) prozor.draw(nep3[i].telo);
//UserInterface
    prozor.draw(healthblank);
    prozor.draw(health);
    prozor.draw(stompblank);
    prozor.draw(stomp);

    prozor.display();
}
void Game::run()
{
    //update
    updateui();
    updatedt();
    if(igrac.stomptime>0) igrac.stomptime-=dt;
    std::cout<<"fps: "<<1.0/dt<<std::endl;

    //game over
    if(igrac.health<=0)
    {
	prozor.close();
	std::cout<<"\n\nGame over. Wanna try again?\n";
	return;
    }

    //izracunajpoz
    for(int i=0;i<nep2.size();i++) nep2[i].izracunajpoz();
    //izracunaj poz i brzinu
    for(int i=0;i<nep3.size();i++)
    {
	if(nep3[i].x<0||nep3[i].x>sirina) nep3[i].vx=-nep3[i].vx;
	if(nep3[i].y<0||nep3[i].y>visina) nep3[i].vy=-nep3[i].vy;
	nep3[i].izracunajpoz();
    }
    //respawn
    time-=dt;
    time2-=dt;
    time3-=dt;
    if(time<0)
    {
	time=8;
	for(int i=0;i<nep.size();i++) if(!nep[i].ziv)
	{
	    nep[i].ziv=1;
	    nep[i].x=Global::rng()%sirina;
	    nep[i].y=Global::rng()%visina;
	}
    }
    if(time2<0)
    {
	time2=14;
	for(int i=0;i<nep2.size();i++) if(!nep2[i].ziv)
	{
	    nep2[i].ziv=1;
	    nep2[i].x=Global::rng()%sirina;
	    nep2[i].y=Global::rng()%visina;
	}
    }
    if(time3<0)
    {
	time3=10;
	for(int i=0;i<nep3.size();i++) if(!nep3[i].ziv)
	{
	    nep3[i].ziv=1;
	    nep3[i].x=Global::rng()%sirina;
	    nep3[i].y=Global::rng()%visina;
	}
    }
    igrac.telo.setPosition(igrac.x,igrac.y);
    //colliding with player
    for(int i=0;i<nep.size();i++) if(nep[i].ziv)
    {
	nep[i].kaigracu(igrac.x,igrac.y,dt);
	nep[i].telo.setPosition(nep[i].x,nep[i].y);
	if(nep[i].telo.getGlobalBounds().intersects(igrac.telo.getGlobalBounds()))
	{
	    nep[i].ziv=0;
	    igrac.health-=Global::rng()%4+1; // 1-4 dmg
	}
    }
    for(int i=0;i<nep2.size();i++) if(nep2[i].ziv)
    {
	nep2[i].brzina(igrac.x,igrac.y,dt);
	nep2[i].telo.setPosition(nep2[i].x,nep2[i].y);
	if(nep2[i].telo.getGlobalBounds().intersects(igrac.telo.getGlobalBounds()))
	{
	    nep2[i].ziv=0;
	    igrac.health-=Global::rng()%8+1; // 1-8 dmg
	}
    }
    for(int i=0;i<nep3.size();i++) if(nep3[i].ziv)
    {
	nep3[i].telo.setPosition(nep3[i].x,nep3[i].y);
	if(nep3[i].telo.getGlobalBounds().intersects(igrac.telo.getGlobalBounds()))
	{
	    nep3[i].ziv=0;
	    igrac.health-=Global::rng()%12+1; // 1-12 dmg
	}
    }
    //debug info
    std::cout<<"Health: "<<igrac.health<<", skor: "<<igrac.xp<<std::endl;
    std::cout<<"Do sledeceg stompa: "<<igrac.stomptime<<std::endl;
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
