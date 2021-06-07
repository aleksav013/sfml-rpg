#ifndef GAME_H
#define GAME_H

#include"Player.hpp"
#include"Enemy1.hpp"
#include"Enemy2.hpp"
#include"Enemy3.hpp"
#include"Powerup.hpp"

#include<memory>
class Game
{
    private:
	std::map<std::string,std::shared_ptr<sf::Font>> font;
	std::map<std::string,std::shared_ptr<sf::Texture>> tex;
	float dt;
	sf::Clock sat,time;

	Player igrac;
	std::vector<Enemy1> nep1;
	std::vector<Enemy2> nep2;
	std::vector<Enemy3> nep3;
	std::vector<Powerup> pow;

	int visina,sirina;
	std::shared_ptr<sf::RenderWindow> prozor;
	
	sf::RectangleShape health,healthblank,stomp,stompblank,vampiric,vampiricblank;
	sf::Text healthtext,stomptext,fps,score,vampirictext;

	void keyboard();
	void run();
	void stompmain();

	void updateui();
	void updatedt();
	void respawn();
	void position();
	void checkcollision();

	void initshapes();
	void initui();
	void inittex();
	void pwptex();
	void initent();
	void updatewin();
    public:
	Game(std::shared_ptr<sf::RenderWindow> mainprozor,std::map<std::string,std::shared_ptr<sf::Font>> mainfont,std::map<std::string,std::shared_ptr<sf::Texture>> maintex);
	void loop(bool ischanged,bool pause);
	void draw();
	bool gameover();
};

#endif
