#include "codegen.hpp"
#include "node.hpp"
#include <iostream>



void CodeGenerator::printCode(const Node &root) {
    bool usedTemp;
    std::string value = printExpression(root,usedTemp);
    if(!usedTemp) {
        printLine(value);
    }
}


std::string CodeGenerator::currentTemp() const {
    if(nextTemp == 1) {
        return "result";
    }
    return "temp" + std::to_string(nextTemp - 1);
}


std::string CodeGenerator::useNextTemp() {
    nextTemp++;
    return currentTemp();
}


void CodeGenerator::printLine(const std::string &text) const {
    std::cout << currentTemp() << " = " << text << "\n";
}


std::string CodeGenerator::printExpression(const Node &node, bool &usedTemp) {
    if(node.children.empty()) {
        usedTemp = false;
        return node.getValue();
    }
    usedTemp = true;
    std::string name = useNextTemp();

    switch(node.getType()) {
        case Token::Type::OPERATOR:
            printOperator(node);
            break;

        case Token::Type::IDENTIFIER:
            printFunctionCall(node);
            break;
            
        default:
            std::cout << "UNKNOWN EXPRESSION\n";
            break;
    }

    return name;
}


void CodeGenerator::printOperator(const Node &node) {
    bool usedTempForLeft, usedTempForRight;

    std::string leftHandSideName = printExpression(node.children[0], usedTempForLeft);
    std::string rightHandSideName =  printExpression(node.children[1], usedTempForRight);

    if(usedTempForLeft) {
        nextTemp--;
    }
    if(usedTempForRight) {
        nextTemp--;
    }

    printLine(leftHandSideName + " " + node.getValue() + " " + rightHandSideName);
}


void CodeGenerator::printFunctionCall(const Node &node) {
    std::string parameterTemps;
    int numberOfTemps = 0;
    for(const Node &child : node.children) {
        bool usedTemp;
        parameterTemps += printExpression(child, usedTemp) + ", ";
        if(usedTemp) {
            numberOfTemps++;
        }
    }

    nextTemp -= numberOfTemps;
    printLine(node.getValue() + "(" + parameterTemps.substr(0, parameterTemps.length() - 2) + ")");
}
