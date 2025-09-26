#pragma once

#include "node.hpp"
#include <string>



class CodeGenerator {
public:
    void printCode(const Node &root);

    
private:
    int nextTemp = 0;
    
    
    std::string currentTemp() const;
    std::string useNextTemp();
    
    void printLine(const std::string &text) const;

    std::string printExpression(const Node &node, bool &usedTemp);
    void printOperator(const Node &node);
    void printFunctionCall(const Node &node);
};
