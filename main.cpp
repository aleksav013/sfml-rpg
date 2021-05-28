#include<iostream>
#include<SFML/Graphics.hpp>
#include<random>
#define seseku(a,b) a.getGlobalBounds().intersects(b.getGlobalBounds())
class Global
{
    public:
	static std::mt19937 rng;
};
std::mt19937 Global::rng = std::mt19937(time(0));
class Entity
{
    public:
	bool ziv=1;
	float x,y;
	sf::RectangleShape telo;
	Entity() {} Entity(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
	void respawn(int sirina,int visina);
};
Entity::Entity(sf::Vector2f pozicija, sf::Vector2f velicina,sf::Color boja)
{
    telo.setSize(velicina);
    telo.setFillColor(boja);
    telo.setOrigin(sf::Vector2f(telo.getSize().x/2,telo.getSize().y/2));
    x=pozicija.x;
    y=pozicija.y; 
}
void Entity::respawn(int sirina,int visina)
{
    if(!ziv)
    {
	x=Global::rng()%sirina;
	y=Global::rng()%visina;
	ziv=1;
    }
}
class Powerup:public Entity 
{
    public:
	static float time;
	Powerup():Entity() {}
	Powerup(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
};
float Powerup::time=20;
Powerup::Powerup(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja)
{

}
class Enemy1:public Entity
{
    private:
	float vx,vy;
    public:
	static float time;
	Enemy1():Entity() {}
	Enemy1(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
	void izracunajbrzinu(float igracx,float igracy);
	void izracunajpoz(float dt);
};
float Enemy1::time=8;
Enemy1::Enemy1(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja) {}
void Enemy1::izracunajbrzinu(float igracx,float igracy)
{
    float k=(igracy-y)/(igracx-x);
    float r=150.0;
    float dx=r/std::sqrt(1+k*k);
    if(igracx-x<0) dx=-dx;
    float dy=k*dx;
    vx=dx;
    vy=dy;
}
void Enemy1::izracunajpoz(float dt)
{
    x+=vx*dt;
    y+=vy*dt;
}
class Enemy2:public Entity
{
    private:
	float vx,vy;
    public:
	static float time;
	Enemy2():Entity() {}
	Enemy2(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
	void izracunajbrzinu(float igracx,float igracy,float dt);
	void izracunajpoz(float igracx,float igracy,float dt);
};
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
class Enemy3:public Entity
{
    public:
	static float time;
	float vx,vy;
	Enemy3():Entity() {}
	Enemy3(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
	void izracunajpoz(float dt);
	void izracunajbrzinu(int sirina,int duzina);
};
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
class Player:public Entity
{
    public:
	int health,xp;
	int stomprad=270;
	float stomptime;

	Player():Entity() {}
	Player(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja);
	void updatest(float dt);
};
Player::Player(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja)
{
    health=100;
    stomptime=0;
    xp=0;
}
void Player::updatest(float dt)
{
    if(stomptime>0) stomptime-=dt;
    else stomptime=0;
}
class Game
{
    private:
	sf::Font font;
	sf::Texture healthtex,neprijateljtex;
	float dt;
	sf::Clock sat,time;

	Player igrac;
	std::vector<Enemy1> nep1;
	std::vector<Enemy2> nep2;
	std::vector<Enemy3> nep3;
	std::vector<Powerup> pow;

	int visina,sirina;
	sf::RenderWindow prozor;
	
	sf::CircleShape krug;
	sf::RectangleShape health,healthblank,stomp,stompblank;

	sf::Text healthtext,stomptext,fps,score;

	void events();
	void keyboard();
	void run();
	void draw();
	void stompmain();

	void updateui();
	void updatedt();
	bool gameover();
	void respawn();
	void position();
	void checkcollision();

	void initshapes();
	void initui();
	void inittex();
	void initent();
	void initwin();
    public:
	Game();
	void loop();
};
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
    if(!font.loadFromFile("assets/fonts/LiberationMono-Regular.ttf"))
    {
	std::cout<<"Font not found\n";
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
    if(!healthtex.loadFromFile("assets/images/healing.png"))
    {
	std::cout<<"Texture not found\n";
    }
    if(!neprijateljtex.loadFromFile("assets/images/nep.png"))
    {
	std::cout<<"Texture not found\n";
    }
    for(size_t i=0;i<pow.size();i++) pow[i].telo.setTexture(&healthtex);
    for(size_t i=0;i<nep1.size();i++) nep1[i].telo.setTexture(&neprijateljtex);
    for(size_t i=0;i<nep2.size();i++) nep2[i].telo.setTexture(&neprijateljtex);
    for(size_t i=0;i<nep3.size();i++) nep3[i].telo.setTexture(&neprijateljtex);
}
void Game::initent()
{
    igrac = Player(sf::Vector2f((float)sirina/2,(float)visina/2),sf::Vector2f(100.0f,100.0f),sf::Color::White);
    for(size_t i=0;i<20;i++) nep1.push_back(Enemy1(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::Red));
    for(size_t i=0;i<7;i++) nep2.push_back(Enemy2(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::Cyan));//(253,106,2)));
    for(size_t i=0;i<4;i++) nep3.push_back(Enemy3(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::Yellow));
    pow.push_back(Powerup(sf::Vector2f(Global::rng()%sirina,Global::rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::White));
}
void Game::initwin()
{
    prozor.create(sf::VideoMode::getFullscreenModes()[0],"RPG igra");
    visina=prozor.getSize().y;
    sirina=prozor.getSize().x;
    prozor.setFramerateLimit(60);
}
Game::Game()
{
    initwin();
    initent();
    initshapes();
    initui();
    inittex();
}
bool Game::gameover()
{
    if(igrac.health<=0)
    {
	prozor.close();
	std::cout<<"\n\nGame over. Wanna try again?\n";
	return 1;
    }
    return 0;
}
void Game::updatedt()
{
    dt=sat.restart().asMicroseconds()/1000000.0;
    fps.setString("fps: "+std::to_string(1/dt));
    score.setString("score: "+std::to_string(time.getElapsedTime().asMilliseconds()/10));
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
    for(size_t i=0;i<nep1.size();i++) if(nep1[i].ziv)
    {
	if(seseku(nep1[i].telo,krug))
	{
	    igrac.xp+=5;
	    nep1[i].ziv=0;
	}
    }
    for(size_t i=0;i<nep2.size();i++) if(nep2[i].ziv)
    {
	if(seseku(nep2[i].telo,krug))
	{
	    igrac.xp+=5;
	    nep2[i].ziv=0;
	}
    }
    for(size_t i=0;i<nep3.size();i++) if(nep3[i].ziv)
    {
	if(seseku(nep3[i].telo,krug))
	{
	    igrac.xp+=5;
	    nep3[i].ziv=0;
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
    for(size_t i=0;i<nep1.size();i++) if(nep1[i].ziv) prozor.draw(nep1[i].telo);
    for(size_t i=0;i<nep2.size();i++) if(nep2[i].ziv) prozor.draw(nep2[i].telo);
    for(size_t i=0;i<nep3.size();i++) if(nep3[i].ziv) prozor.draw(nep3[i].telo);
    for(size_t i=0;i<pow.size();i++) if(pow[i].ziv) prozor.draw(pow[i].telo);

    prozor.draw(healthblank);
    prozor.draw(health);
    prozor.draw(healthtext);
    prozor.draw(stompblank);
    prozor.draw(stomp);
    prozor.draw(stomptext);
    prozor.draw(fps);
    prozor.draw(score);

    prozor.display();
}
void Game::position()
{
    igrac.telo.setPosition(igrac.x,igrac.y);
    for(size_t i=0;i<nep1.size();i++) if(nep1[i].ziv)
    {
	nep1[i].izracunajbrzinu(igrac.x,igrac.y);
	nep1[i].izracunajpoz(dt);
	nep1[i].telo.setPosition(nep1[i].x,nep1[i].y);
    }
    for(size_t i=0;i<nep2.size();i++) if(nep2[i].ziv)
    {
	nep2[i].izracunajbrzinu(igrac.x,igrac.y,dt);
	nep2[i].izracunajpoz(igrac.x,igrac.y,dt);
	nep2[i].telo.setPosition(nep2[i].x,nep2[i].y);
    }
    for(size_t i=0;i<nep3.size();i++) if(nep3[i].ziv)
    {
	nep3[i].izracunajbrzinu(sirina,visina);
	nep3[i].izracunajpoz(dt);
	nep3[i].telo.setPosition(nep3[i].x,nep3[i].y);
    }
    for(size_t i=0;i<pow.size();i++) if(pow[i].ziv)
    {
	pow[i].telo.setPosition(pow[i].x,pow[i].y);
    }
}
void Game::checkcollision()
{
    for(size_t i=0;i<nep1.size();i++) if(nep1[i].ziv)
    {
	if(seseku(nep1[i].telo,igrac.telo))
	{
	    nep1[i].ziv=0;
	    igrac.health-=Global::rng()%4+1; // 1-4 dmg
	}
    }
    for(size_t i=0;i<nep2.size();i++) if(nep2[i].ziv)
    {
	if(seseku(nep2[i].telo,igrac.telo))
	{
	    nep2[i].ziv=0;
	    igrac.health-=Global::rng()%8+1; // 1-8 dmg
	}
    }
    for(size_t i=0;i<nep3.size();i++) if(nep3[i].ziv)
    {
	if(seseku(nep3[i].telo,igrac.telo))
	{
	    nep3[i].ziv=0;
	    igrac.health-=Global::rng()%12+1; // 1-12 dmg
	}
    }
    for(size_t i=0;i<pow.size();i++) if(pow[i].ziv)
    {
	if(seseku(pow[i].telo,igrac.telo))
	{
	    pow[i].ziv=0;
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
	for(size_t i=0;i<nep1.size();i++) nep1[i].respawn(sirina,visina);
    }
    if(Enemy2::time<0)
    {
	Enemy2::time=14;
	for(size_t i=0;i<nep2.size();i++) nep2[i].respawn(sirina,visina);
    }
    if(Enemy3::time<0)
    {
	Enemy3::time=10;
	for(size_t i=0;i<nep3.size();i++) nep3[i].respawn(sirina,visina);
    }
    if(Powerup::time<0)
    {
	Powerup::time=20;
	for(size_t i=0;i<pow.size();i++) pow[i].respawn(sirina,visina);
    }
}
void Game::run()
{
    if(gameover()) return;

    updateui();
    updatedt();
    igrac.updatest(dt);

    respawn();
    position();
    checkcollision();
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
