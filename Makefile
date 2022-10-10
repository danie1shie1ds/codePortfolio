# Author: Daniel Shields
# E-mail: dshield2@nd.edu
# this is the Makefile for Programming Challenge 04

# g++ is the GCC compiler for C++
CC := g++

# CXXFLAGS are the compiler flags for when we compile C++ code in this course
FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -Werror -lm
CXXFLAGS := -m64 -std=c++11 $(FLAGS)

# Folder Variables
INC := include
SRC := src
OBJ := objects
EXE := exe

# Make initialize - Create the objects and executables

initialize:
	rm -rf $(OBJ) $(EXE)
	mkdir $(OBJ) $(EXE)
#Create the Singly Linked List Object
$(OBJ)/PC04.o: $(SRC)/PC04.cpp
	$(CC) $(CXXFLAGS) -c $(SRC)/PC04.cpp -o $@
# Create the Singly Linked List Object
$(OBJ)/game.o: $(SRC)/game.cpp
	$(CC) $(CXXFLAGS) -c $(SRC)/game.cpp -o $@
	
# Singly Linked List Objects
PC04_objs := $(OBJ)/PC04.o $(OBJ)/game.o

# Singly Linked List Executable and Run
PC04: $(PC04_objs)
	$(CC) $(CXXFLAGS) -o $(EXE)/PC04 $(PC04_objs)

# Make Clean
clean:
	rm -rf $(OBJ)/* $(EXE)/*