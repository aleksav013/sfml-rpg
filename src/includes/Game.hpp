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
	sf::RenderWindow *prozor;
	
	sf::CircleShape krug;
	sf::RectangleShape health,healthblank,stomp,stompblank;
	sf::Text healthtext,stomptext,fps,score;

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
	void updatewin();
    public:
	Game() {}
	Game(sf::RenderWindow *glprozor);
	void loop(bool ischanged,bool pause);
};

#endif
