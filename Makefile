# Compiler
CC = g++

# Flags for error detection
CFLAGS = -Wall -Wextra

# Files to compile
OBJS = logicsolver.cpp parser.cpp stringvisitor.cpp

# Executable name
ONAME = solver

all : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(ONAME) 
