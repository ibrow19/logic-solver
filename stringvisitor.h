#ifndef STRING_VISITOR_ASDHGASKDGHKJASDGSAKHDGJ
#define STRING_VISITOR_ASDHGASKDGHKJASDGSAKHDGJ

#include <string>
#include <map>

#include "visitor.h"
#include "parser.h"


/*
 * Visitor class which takes a map of variables to their values in a context a 
 *  builds a row in a truth table showing the result of each sub formula in a 
 *  formula with the given context. The string representing the result is 
 *  aligned with the string representation of the formula for creating a truth 
 *  table.
 */
class ResultBuildVisitor: public FormulaVisitor {
public:

    ResultBuildVisitor(std::map<char, bool> m);

    // Getter for result
    std::string getResult() const;

    void visit(const Formula* f);
    void visit(const Atomic* a);
    void visit(const Negated* n);
    void visit(const Compound* c);

private:

    // bool to char conversion to be used for changing eval from parse tree to 
    //  1 or 0.
    char boolToChar(bool b) const;

    std::string result;
    std::map<char, bool> context;
    
};


#endif
