#ifndef PARSER_HEADER_ASJFOASJDASODJASODUASOUDHN
#define PARSER_HEADER_ASJFOASJDASODJASODUASOUDHN

#include <istream>
#include <string>
#include <exception>
#include <map>
#include <set>


// Forward declaration of visitor class so it can be used in this file.
class FormulaVisitor;


/*
 * Abstract class defining basic interface for formula parsing classes.
 */
class FormulaProduction {
public:

    // Default destructor to be overridden by subclasses if necessary.
    virtual ~FormulaProduction();

    // Getter for variables in formula.
    std::set<char> getVars() const;

    // Gets string representation of formula: what would be parsed to create
    //  that formula.
    virtual std::string getStringVal() const = 0;

    // Evaluates the formula as true or false.
    // varVals is a map of variables to the true/false value they should be
    //  evaluated as.
    // If not all variables in the formula are in the map then an error will be thrown.
    virtual bool eval(const std::map<char,bool>& varVals) const = 0;

    // Accepts a visitor class to traverse the parse tree and carry out an operation
    virtual void accept(FormulaVisitor& v) const = 0;

protected:

    // Set of all boolean variables in the formula.
    std::set<char> vars;
};


/*
 * Exception to throw when there is an error parsing an expression
 */
class ParseError : public std::exception {
private:

    // Gives meaningful error message.
    const char* what() const throw();

};


/*
 * Class for parsing a generic formula from an input stream
 * Uses the input stream to determine which type of formula it represents
 */
class Formula : public FormulaProduction {
public:
    Formula(std::istream& in);
    ~Formula();
    std::string getStringVal() const;
    bool eval (const std::map<char,bool>& varVals) const;
    void accept(FormulaVisitor& v) const;

    // Gets val, pointer to const return so cannot be deleted, tree should only
    //  be deletable from root.
    const FormulaProduction* getFormula() const;

private:

    // Points to a formula based on input.
    FormulaProduction* val;
};


/*
 * Class for parsing an atomic formula: a boolean variable or a constant.
 */
class Atomic : public FormulaProduction {
public:
    Atomic(std::istream& in);
    std::string getStringVal() const;
    bool eval (const std::map<char,bool>& varVals) const;
    void accept(FormulaVisitor& v) const;

private:

    // Value of this atomic formula, a boolean variable or a 1 or 0 for a constant.
    char val;
};


/* 
 * Class for parsing a Negated formula.
 */
class Negated : public FormulaProduction {
public:
    Negated(std::istream& in);
    ~Negated();
    std::string getStringVal() const;
    bool eval (const std::map<char,bool>& varVals) const;
    void accept(FormulaVisitor& v) const;

    // Gets val
    const Formula* getNegated() const; 

private:
    
    // Pointer to the formula that is being negated.
    Formula* val;
};


/*
 * Class for parsing a compound formula
 */
class Compound : public FormulaProduction {
public:
    Compound(std::istream& in);
    ~Compound();
    std::string getStringVal() const;
    bool eval (const std::map<char,bool>& varVals) const;
    void accept(FormulaVisitor& v) const;

    // Getters for formula making up compound
    const Formula* getFirst() const; 
    const Formula* getSecond() const; 

private:

    // Formulas that make up the compound formula
    Formula* firstVal;
    Formula* secondVal;

    // Character representation of operation for this formula
    char op;
};


#endif
