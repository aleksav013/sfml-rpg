#ifndef GAME_H
#define GAME_H

#include"Player.hpp"
#include"Enemy1.hpp"
#include"Enemy2.hpp"
#include"Enemy3.hpp"
#include"Powerup.hpp"

class Game
{
    private:
	std::map<std::string,sf::Font*> font;
	std::map<std::string,sf::Texture*> tex;
	float dt;
	sf::Clock sat,time;

	Player igrac;
	std::vector<Enemy1> nep1;
	std::vector<Enemy2> nep2;
	std::vector<Enemy3> nep3;
	std::vector<Powerup> pow;

	int visina,sirina;
	sf::RenderWindow *prozor;
	
	sf::RectangleShape health,healthblank,stomp,stompblank;
	sf::Text healthtext,stomptext,fps,score;

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
	void initent();
	void updatewin();
    public:
	Game();
	Game(sf::RenderWindow *glprozor,std::map<std::string,sf::Font*> mainfont,std::map<std::string,sf::Texture*> maintex);
	void loop(bool ischanged,bool pause);
	void draw();
	bool gameover();
};

#endif
