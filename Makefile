CXX = g++
CXXFLAGS = --std=c++14 -g -O2 -Wall
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

SOURCE_DIR = src/
OBJECTS_DIR= obj/
OBJS = main.o State.o Game.o Global.o Enemy1.o Enemy2.o Enemy3.o Powerup.o Entity.o Player.o
OBJECTS = $(addprefix $(OBJECTS_DIR),$(OBJS))

TARGET = sfml-rpg

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDLIBS)

$(OBJECTS_DIR)%.o: $(SOURCE_DIR)%.cpp
	$(MKDIR_P) $(dir  $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) sfml-rpg

RM = rm -f
MKDIR_P = mkdir -p
