#ifndef GLOBAL_H
#define GLOBAL_H

#include<random>
#define seseku(a,b) a.getGlobalBounds().intersects(b.getGlobalBounds())
class Global
{
    public:
	static std::mt19937 rng;
};

#endif
