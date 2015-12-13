#compiler to use
CXX=g++-4.9
#arguments for compile
CPPFLAGS=-c -g -std=c++0x -Wall -I$(INC_PATH)	#-Wall -Wextra
LDFLAGS= -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

INC_PATH= /home/aarni/Ohjelmointi/Kirjastot/SFML-2.3.2/include
LIB_PATH= /home/aarni/Ohjelmointi/Kirjastot/SFML-2.3.2/lib
#Directories
SRC_DIR = src
OBJ_DIR = src
HDR_DIR = src
TEST_DIR = test

#src files
SOURCES=$(SRC_DIR)/main.cpp $(SRC_DIR)/AI.cpp $(SRC_DIR)/Block.cpp $(SRC_DIR)/Button.cpp $(SRC_DIR)/Config.cpp $(SRC_DIR)/Editor.cpp $(SRC_DIR)/Engine.cpp $(SRC_DIR)/Game.cpp $(SRC_DIR)/Hitbox.cpp $(SRC_DIR)/Map.cpp $(SRC_DIR)/Menu.cpp $(SRC_DIR)/Object.cpp $(SRC_DIR)/Player.cpp $(SRC_DIR)/Projectile.cpp $(SRC_DIR)/ResourceManager.cpp $(SRC_DIR)/Vehicle.cpp
#.o files, which are used to make the executable (building .cpp and .hpp result in to these), could be $(SOURCES:.cpp=.o) as well
OBJECTS=$(OBJ_DIR)/main.o $(OBJ_DIR)/Block.o $(OBJ_DIR)/Button.o $(OBJ_DIR)/Config.o $(OBJ_DIR)/Editor.o $(OBJ_DIR)/Engine.o $(OBJ_DIR)/Game.o $(OBJ_DIR)/Hitbox.o $(OBJ_DIR)/Map.o $(OBJ_DIR)/Menu.o $(OBJ_DIR)/Object.o $(OBJ_DIR)/Player.o $(OBJ_DIR)/Projectile.o $(OBJ_DIR)/ResourceManager.o $(OBJ_DIR)/Vehicle.o
#header files that src files are dependant on
DEPS=$(HDR_DIR)/AI.h $(HDR_DIR)/Block.h $(HDR_DIR)/Button.h $(HDR_DIR)/Config.h $(HDR_DIR)/Editor.h $(HDR_DIR)/Engine.h $(HDR_DIR)/Game.h $(HDR_DIR)/Hitbox.h $(HDR_DIR)/Map.h $(HDR_DIR)/Menu.h $(HDR_DIR)/Object.h $(HDR_DIR)/Player.h $(HDR_DIR)/Projectile.h $(HDR_DIR)/ResourceManager.h $(HDR_DIR)/Vehicle.h

#what we want as result: now we get main executable, which we can run
EXECUTABLE=main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	${CXX} -o $@ ${OBJECTS} -L$(LIB_PATH) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(CPPFLAGS) $(SOURCES)

#.cpp.o: $(DEPS)
#	${CXX} ${CPPFLAGS} $(SOURCES)

clean:
	rm -f $(OBJ_DIR)/*.o
