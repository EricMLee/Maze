#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 4
#
#  make                     makes FindPath
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on in3
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

Maze : Maze.o $(BASE_OBJECTS)
	$(LINK) Maze Maze.o $(BASE_OBJECTS)

Maze.o : Maze.c $(HEADERS)
	$(COMPILE) Maze.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) Maze Maze.o $(BASE_OBJECTS)

checkFind : Maze
	$(MEMCHECK) Maze in3 junk3

checkClient : GraphTest