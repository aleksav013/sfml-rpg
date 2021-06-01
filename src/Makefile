CXX = g++
CXXFLAGS = --std=c++14 -g -O2 -Wall
SRC_DIR = src/
OBJECTS = main.o State.o Game.o Global.o Enemy1.o Enemy2.o Enemy3.o Powerup.o Entity.o Player.o

all: sfml-rpg

sfml-rpg: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o sfml-rpg -lsfml-graphics -lsfml-window -lsfml-system

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) sfml-rpg
