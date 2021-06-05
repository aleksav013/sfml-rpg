#ifndef STATE_H
#define STATE_H

#include<SFML/Graphics.hpp>
class State
{
    private:
	sf::RenderWindow prozor;
	int visina,sirina;
	bool ischanged=0,newgame=0,pause=0,kraj=0;

	std::map<std::string,sf::Font*> font;
	std::map<std::string,sf::Texture*> tex;

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
