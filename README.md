# logic-solver
A parser for logic propositions. In addition to the parser is a visitor 
interface in visitor.h for adding additional functions without changing 
the base parser interface. The string visitor files implement an example
visitor which is used in logicsolver.cpp to parse a logic proposition from
the user and form a truth table for it. The visitor in stringvisitor.cpp
builds the rows in the tuth table.

The program can be compiled using the rules defined in Makefile with 'make' 
and run with './solver'.
