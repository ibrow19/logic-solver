#ifndef VISITOR_HEADER_SDKJDAHGKFJADGFKJASHGDF
#define VISITOR_HEADER_SDKJDAHGKFJADGFKJASHGDF


class Formula;
class Atomic;
class Negated;
class Compound;


/*
 * Class defining interface for visitors of formulas
 * The goal of this visitor class is to allow for addition of more complex
 *  opeartions to the tree created by the parser in parser.h/parser.cpp without
 *  complicating/changing the base interface
 */
class FormulaVisitor {
public:
    virtual ~FormulaVisitor() {};

    // Visit function for each type of formula.
    virtual void visit(const Formula* f) = 0;
    virtual void visit(const Atomic* a) = 0;
    virtual void visit(const Negated* n) = 0;
    virtual void visit(const Compound* c) = 0;
};


#endif
