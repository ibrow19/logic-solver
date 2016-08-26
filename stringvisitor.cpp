#include "stringvisitor.h"


/* ResultBuildVisitor Class */

ResultBuildVisitor::ResultBuildVisitor(std::map<char, bool> m) : context(m) {}


std::string ResultBuildVisitor::getResult() const {

    return result;

}


void ResultBuildVisitor::visit(const Formula* f) {

    (f->getFormula())->accept(*this);

}


void ResultBuildVisitor::visit(const Atomic* a) {

    result += boolToChar(a->eval(context));

}


void ResultBuildVisitor::visit(const Negated* n) {

    result += boolToChar(n->eval(context));

    (n->getNegated())->accept(*this);

}


void ResultBuildVisitor::visit(const Compound* c) {

    // Space for alignment with brackets;
    result += ' ';

    (c->getFirst())->accept(*this);

    result += boolToChar(c->eval(context));

    (c->getSecond())->accept(*this);

    result += ' ';

}


char ResultBuildVisitor::boolToChar(bool b) const {

    return (b ? '1' : '0');

}
