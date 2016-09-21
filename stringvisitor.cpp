#include "stringvisitor.hpp"


/* ResultBuildVisitor Class */

ResultBuildVisitor::ResultBuildVisitor(std::map<char, bool> m) : context(m) {}


void ResultBuildVisitor::visit(const Formula* f) {

    (f->getFormula())->accept(*this);

}


// This visitor does not use parameter so is commented out.
void ResultBuildVisitor::visit(const Atomic* /* a */) {

    // Don't need to display result for Atomics as all variable values shown
    //  at start of row.
    result << ' ';

}


void ResultBuildVisitor::visit(const Negated* n) {

    result << (n->eval(context));

    (n->getNegated())->accept(*this);

}


void ResultBuildVisitor::visit(const Compound* c) {

    // Space for alignment with brackets;
    result << ' ';

    (c->getFirst())->accept(*this);

    result << (c->eval(context));

    (c->getSecond())->accept(*this);

    result << ' ';

}


std::string ResultBuildVisitor::getResult() const {

    return result.str();

}
