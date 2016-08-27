# Files to compile
OBJS = logicsolver.cpp parser.cpp stringvisitor.cpp

CC = g++

COMPILER_FLAGS = -Wall -Wextra

# Libraries being linked
#LINKER_FLAGS = 

# executable name
OBJ_NAME = solver

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME) 
