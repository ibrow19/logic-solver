# Compiler
CC = g++

# Flags for error detection
CFLAGS = -Wall -Wextra

# Files to compile
OBJS = logicsolver.cpp parser.cpp stringvisitor.cpp

# Executable name
ONAME = solver

all : $(OBJS) visitor.hpp parser.hpp stringvisitor.hpp
	$(CC) $(OBJS) $(CFLAGS) -o $(ONAME) 
