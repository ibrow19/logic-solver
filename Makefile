# Files to compile
OBJS = logicsolver.cpp parser.cpp stringvisitor.cpp

CC = g++

COMPILER_FLAGS = -Wall -Wextra -std=c++11

# Libraries being linked
#LINKER_FLAGS = 

# executable name
OBJ_NAME = solver

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME) 
