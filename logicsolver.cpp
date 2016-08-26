#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include "parser.h"
#include "stringvisitor.h"


int main(int argc, char* const argv[]) {

    if (argc != 2) {

        std::cout << "usage: <> <proposition>" << std::endl;
        return 0;
        
    }

    std::stringstream propStream(argv[1]);

    try {

        Formula prop(propStream);
        



        std::map<char, bool> varVals;

        varVals['a'] = true;
        varVals['b'] = false;

        ResultBuildVisitor v(varVals);

        prop.accept(v);

        std::cout << (v.getResult()) << std::endl;



    } catch (std::exception& e) {

        std::cout << e.what() << std::endl;

    }

}

