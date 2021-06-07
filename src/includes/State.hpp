#ifndef STATE_H
#define STATE_H

#include<SFML/Graphics.hpp>
#include<memory>
class State
{
    private:
	std::shared_ptr<sf::RenderWindow> prozor;
	int visina,sirina;
	bool ischanged=0,newgame=0,pause=0,kraj=0;

	std::map<std::string,std::shared_ptr<sf::Font>> font;
	std::map<std::string,std::shared_ptr<sf::Texture>> tex;

	sf::RectangleShape podloga;
	sf::Text pausetext,krajtext;

	void initassets();
	void initwin();
	void initui();
	void updateui();
	void events();
	void keyboard();
    public:
	State();
	void loop();
};

#endif
