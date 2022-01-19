RM = rm -f
MKDIR = mkdir -p

CXX = g++
CXXFLAGS = --std=c++14 -O3 -Wall
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

SOURCE_DIR = src
OBJECT_DIR= build
OBJS = main.o State.o Game.o Global.o Enemy1.o Enemy2.o Enemy3.o Powerup.o Entity.o Player.o
OBJECTS = $(addprefix $(OBJECT_DIR)/,$(OBJS))

TARGET = sfml-rpg

.PHONY: all compile clean

all: compile

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDLIBS)

compile:
	$(MKDIR) $(OBJECT_DIR)
	$(MAKE) $(TARGET)

run: compile
	./$(TARGET)

clean:
	$(RM) $(OBJECTS) sfml-rpg

-include $(OBJECTS:.o=.d)
