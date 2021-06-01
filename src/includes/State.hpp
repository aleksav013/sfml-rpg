#ifndef STATE_H
#define STATE_H

#include<SFML/Graphics.hpp>
class State
{
    private:
	sf::RenderWindow prozor;
	int visina,sirina;
	bool ischanged=0,pause=0;

	void events();
	void keyboard();
    public:
	State();
	void loop();
};

#endif
