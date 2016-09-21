#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include "parser.hpp"
#include "stringvisitor.hpp"


int main(int argc, char* const argv[]) {

    if (argc != 2) {

        std::cout << "usage: <exec> <proposition>" << std::endl;
        return 0;
        
    }

    std::stringstream propStream(argv[1]);

    try {

        Formula prop(propStream);
        

        std::map<char, bool> varVals;

        std::set<char> vars = prop.getVars();

        // Fill map with default value for each variable in input proposition.
        // At the same time, output column headers for each variable.
        std::set<char>::iterator it;
        for (it = vars.begin(); it != vars.end(); ++it) {

            char variable = *it;
            std::cout << variable;
            varVals[variable] = false;

        }


        // Output string version of formula at the top.
        std::cout << ' ' << prop.getStringVal() << std::endl;


        // Height of table equal to all possible combination of variables. 
        // (2^ No. of vars)
        int height = pow(2, varVals.size());
 
        for (int h = 0; h < height; ++h) {
 
            // lineNum keeps track of current row in table.
            int lineNum = h;

            // For each line use boolean representation of that line for 
            //  value of variables.
            std::map<char, bool>::reverse_iterator rit;
            for (rit = varVals.rbegin(); rit != varVals.rend(); ++rit) {

                if (lineNum == 0) {
 
                    rit->second = false;
 
                } else {

                    if (lineNum % 2 == 1) {

                        rit->second = true;

                    } else {

                        rit->second = false;

                    }

                    lineNum /= 2;

                }

            }

            // Output variable values for this row.
            std::map<char, bool>::iterator mapit;
            for (mapit = varVals.begin(); mapit != varVals.end(); ++mapit) {

                std::cout << mapit->second;

            }

            // Output results.
            ResultBuildVisitor v(varVals);

            prop.accept(v);

            // Output overall result of proposition at end.
            std::cout << ' ' << v.getResult() << ':' << prop.eval(varVals) << std::endl;

        }


    } catch (std::exception& e) {

        std::cout << e.what() << std::endl;

    }

}

