#include<iostream>
#include<SFML/Graphics.hpp>
#include<random>
std::mt19937 rng(time(0));
const int n=20;
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
	bool ziv=1;
	Enemy():Entity() {}
	Enemy(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja) {}
	void kaigracu(float igracx,float igracy);
};
void Enemy::kaigracu(float igracx,float igracy)
{
	float k=(igracy-y)/(igracx-x);
	float r=1.0;
	float dx=r/std::sqrt(1+k*k);
	if(igracx-x<0) dx=-dx;	
	float dy=k*dx;
	
	x+=dx;
	y+=dy;

}
class Player:public Entity
{
    public:
	int health,xp;
	int stomprad=300;
	float stomptime;
	
	Player():Entity() {}
	Player(sf::Vector2f pozicija,sf::Vector2f velicina,sf::Color boja):Entity(pozicija,velicina,boja) 
	{
	    health=100;
	    xp=0;
	    stomptime=0;
	}
	void stomp(Enemy neprijatelj[]);
};
void Player::stomp(Enemy neprijatelj[])
{
    stomptime=3;
    for(int i=0;i<n;i++) if(neprijatelj[i].ziv)
    {
	if((x-neprijatelj[i].x)*(x-neprijatelj[i].x)+(y-neprijatelj[i].y)*(y-neprijatelj[i].y)<stomprad*stomprad)
	{
	    xp+=5;
	    neprijatelj[i].ziv=0;
	}
    }
}
class Game
{
    float time;
    Player igrac;
    Enemy neprijatelj[n];
    sf::RenderWindow prozor;
    int visina,sirina;
    sf::CircleShape krug;
    public:
	Game();
	void loop();
	void events();
	void keyboard();
	void run();
	void draw();
	void stompmain();
};
Game::Game()
{
    time=5;
    prozor.create(sf::VideoMode(512,512),"RPG igra");
    visina=prozor.getSize().y;
    sirina=prozor.getSize().x;
    prozor.setFramerateLimit(60);
    igrac = Player(sf::Vector2f((float)sirina/2,(float)visina/2),sf::Vector2f(100.0f,100.0f),sf::Color::White);
    for(int i=0;i<n;i++) neprijatelj[i] = Enemy(sf::Vector2f(rng()%sirina,rng()%visina),sf::Vector2f(50.0f,50.0f),sf::Color::Red);
    igrac.x=(float)prozor.getSize().x/2;
    igrac.y=(float)prozor.getSize().y/2;

    krug.setRadius(igrac.stomprad);
    krug.setFillColor(sf::Color::Black);
    krug.setOutlineThickness(10);
    krug.setOutlineColor(sf::Color::White);
    krug.setOrigin(krug.getRadius(),krug.getRadius());
}
void Game::stompmain()
{
    igrac.stomp(neprijatelj);
    krug.setPosition(igrac.x,igrac.y);
}
void Game::keyboard()
{
    float dist=10.0;
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
	}
    }
    keyboard();
}
void Game::draw()
{
    prozor.clear();
    if(igrac.stomptime>2.8) prozor.draw(krug);
    prozor.draw(igrac.telo);
    for(int i=0;i<n;i++) if(neprijatelj[i].ziv) prozor.draw(neprijatelj[i].telo);
    prozor.display();
}
void Game::run()
{
    if(igrac.health<=0)
    {
	prozor.close();
	std::cout<<"\n\nGame over. Wanna try again?\n";
	return;
    }

    time-=0.01;
    if(time<0)
    {
	time=5;
	for(int i=0;i<n;i++) if(!neprijatelj[i].ziv)
	{
	    neprijatelj[i].ziv=1;
	    neprijatelj[i].x=rng()%sirina;
	    neprijatelj[i].y=rng()%visina;
	}
    }
    if(igrac.stomptime>0) igrac.stomptime-=0.01;
    igrac.telo.setPosition(igrac.x,igrac.y);
    for(int i=0;i<n;i++) if(neprijatelj[i].ziv)
    {
	neprijatelj[i].kaigracu(igrac.x,igrac.y);
	neprijatelj[i].telo.setPosition(neprijatelj[i].x,neprijatelj[i].y);
	if(neprijatelj[i].telo.getGlobalBounds().intersects(igrac.telo.getGlobalBounds()))
	{
	    neprijatelj[i].ziv=0;
	    igrac.health--;
	}
    }
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
