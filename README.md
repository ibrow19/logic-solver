# logic-solver
A parser for logic propositions. In addition to the parser is a visitor 
interface in visitor.h for adding additional functions without changing 
the base parser interface. The string visitor files implement an example
visitor which is used in logicsolver.cpp to parse a logic proposition from
the user and form a truth table for it. The visitor in stringvisitor.cpp
builds the rows in the tuth table.

-USAGE-

The program can be compiled using the rules defined in Makefile with 'make' 
and run with './solver'.

The program takes a single argument which is a logic formula. Atomic formulas
are of the form of a single upper or lower case letter (case sensitive so 'A'
is a different variable to 'a'). A negated formula is any fomrula preceded
by a '-'. A compound formula must begin with '(' and end with ')' and takes
the general form "(x&y)" where x and y can be any formula and '&' can be any
of the following operators:
    & - and
    | - or
    # - xor
    > - implies
    = - equals
