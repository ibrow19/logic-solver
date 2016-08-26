#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <cmath>

#include "parser.h"


/* FormulaProduction Class */

// Default destructor to be overridden
FormulaProduction::~FormulaProduction() {}


std::set<char> FormulaProduction::getVars() const{

    return vars;

}


void FormulaProduction::accept(FormulaVisitor& v) {

    v.visit(this);

}


/* ParseError Class */

const char* ParseError::what() const throw(){

    return "Parsing error occured";

}


/* Formula class */

Formula::Formula(std::istream& in) {

    char next = in.peek();

    if (next == '(') {
        
        val = new Compound(in);

    } else if (next == '-') {

        val = new Negated(in);
    
    } else if (isalpha(next) || next == '1' || next == '0') {

        val = new Atomic(in);

    } else {

        throw ParseError();

    }

    // Get set of variables from child.
    vars = val->getVars();

}


Formula::~Formula() {

    delete val;

}


std::string Formula::getStringVal() const {

    return val->getStringVal();

}


bool Formula::eval(const std::map<char, bool>& varVals) const {

    return val->eval(varVals);

}


FormulaProduction const* Formula::getFormula() const {

    return val;

}


/* Atomic class */

Atomic::Atomic(std::istream& in) {

    char next = in.peek();

    if (isalpha(next) || next == '1' || next == '0') {

        in >> val;

    } else {

        throw ParseError();

    }

    // Create set with variable or default uses empty set if 1 or 0.
    if (val != '1' && val != '0') {

        vars = {val};

    }

}


std::string Atomic::getStringVal() const {

    return std::string(1,val);

}


bool Atomic::eval(const std::map<char, bool>& varVals) const {

    if (val == '1') {

        return true;

    } else if (val == '0') {

        return false;

    } else {

        return varVals.at(val);

    }

}


void Atomic::accept(FormulaVisitor& v) {

    v.visit(this);

}


/* Negated class */

Negated::Negated(std::istream& in) {

    if (in.peek() == '-') {

        in.get();
        val = new Formula(in);

        // Get set of variables from negated formula.
        vars = val->getVars();

    } else {

        throw ParseError();

    }

}


Negated::~Negated() {

    delete val;

}


std::string Negated::getStringVal() const {

    return '-' + val->getStringVal();

}


bool Negated::eval(const std::map<char, bool>& varVals) const {

    return !(val->eval(varVals));

}


void Negated::accept(FormulaVisitor& v) {

    v.visit(this);

}


Formula const* Negated::getNegated() {

    return val;

}


/* Compound class */


// TODO: Check for memory leaks that might occur here
Compound::Compound(std::istream& in) {

    if (in.peek() == '(') {

        in.get();
        firstVal = new Formula(in);

        char next = in.peek();
        if (next != '|' && next != '&' && next != '#' && next != '>' && next != '=') {

            throw ParseError();

        }

        in >> op;
        secondVal = new Formula(in);

        if (in.peek() == ')') {

            in.get();

        } else {

            throw ParseError();

        }


    } else {

        throw ParseError();

    }
    
    // Combine variables from chldren for set of variables in compound.
    std::set<char> firstSet = firstVal->getVars();
    std::set<char> secondSet = secondVal->getVars();
    std::set_union(firstSet.begin(), 
                   firstSet.end(),
                   secondSet.begin(), 
                   secondSet.end(), 
                   std::inserter(vars, vars.end()));
    

}


Compound::~Compound() {

    delete firstVal;
    delete secondVal;

}


std::string Compound::getStringVal() const {

    return '(' + firstVal->getStringVal() + op + secondVal->getStringVal() + ')';

}


bool Compound::eval(const std::map<char, bool>& varVals) const {

    bool res1 = firstVal->eval(varVals);
    bool res2 = secondVal->eval(varVals);

    switch(op) {
        case '|':
            return (res1 || res2);
            break;

        case '&':
            return (res1 && res2);
            break;

        case '#':
            return ((res1 && !res2) || (res2 && !res1));
            break;

        case '>':
            return (!(res1 && !res2));
            break;

        default:
            return (res1 == res2)

    }


}


Formula const* getFirst() const {

    return FirstVal;

}


Formula const* getSecond() const {

    return secondVal;

}
