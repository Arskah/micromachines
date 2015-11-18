#compiler to use
CC=g++
#arguments for compile
CPPFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic
#src files
SOURCES=main.cpp AI.cpp Block.cpp Config.cpp Editor.cpp Engine.cpp Game.cpp Map.cpp Menu.cpp Object.cpp Player.cpp Projectile.cpp Vehicle.cpp
#.o files, which are used to make the executable (building .cpp and .hpp result in to these), could be $(SOURCES:.cpp=.o) as well
OBJECTS=main.o Block.o Config.o Editor.o Engine.o Game.o Map.o Menu.o Object.o Player.o Projectile.o Vehicle.o
#header files that src files are dependant on
DEPS=AI.h Block.h Config.h Editor.h Engine.h Game.h Map.h Menu.h Object.h Player.h Projectile.h Vehicle.h
#we use SFML library, so we must tell Make where the lib files are
INCLUDES=-I/home/aarni/Ohjelmointi/Kirjastot/SFML/include
LIBS=-L/home/aarni/Ohjelmointi/Kirjastot/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
#what we want as result: now we get main executable, which we can run
EXECUTABLE=main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	${CC} ${OBJECTS} -o $@ ${LIBS}

.cpp.o: $(DEPS)
	${CC} ${CPPFLAGS} $(SOURCES) ${INCLUDES}

clean:
	rm -f $(OBJECTS) *.o
