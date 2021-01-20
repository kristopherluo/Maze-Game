CC = g++
C = cpp
H = h
NAME = amaze

# path to directory holding the ezdraw.h file
IDIR = ../
# path to the directory holding the libezdraw.a files
LDIR = ../

# loader flags showing where to find the SDL libraries
LDFLAGS = `sdl2-config --libs`

# non SDL libraries to load: ezdraw and math library
LIBS = -lezdraw -lm

# compiler flags for maximum warnings, debugger information,
# and where to find SDL include files
CFLAGS = `sdl2-config --cflags` -g -W -Wall -Wextra -pedantic -O0 -I `sdl2-config --prefix`/include/

HFILES = Maze.${H} Room.${H} Player.${H}
OFILES = Maze.o Room.o Player.o

PROJECT = amaze

${PROJECT}:	${PROJECT}.o ${OFILES}
	${CC} -g -o ${PROJECT} ${PROJECT}.o ${OFILES} -L $(LDIR) $(LIBS) $(LDFLAGS)

${PROJECT}.o: ${PROJECT}.${C} ${HFILES}
	${CC} ${CFLAGS} -c -I $(IDIR) ${PROJECT}.${C}

Maze.o:  Maze.$(C) Maze.${H} Room.${H}
	${CC} ${CFLAGS} -c -I $(IDIR) Maze.${C}

Room.o:  Room.${C} Room.${H} Maze.${H}
	${CC} ${CFLAGS} -c -I $(IDIR) Room.${C}

Player.o:  Player.${C} Player.${H} Maze.${H}
	${CC} ${CFLAGS} -c -I $(IDIR) Player.${C}

clean:
	rm -f *.o *~ ${PROJECT}
