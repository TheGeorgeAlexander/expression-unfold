#pragma once

#include "node.hpp"
#include <string>



class CodeGenerator {
public:
    void generateCode(const Node &root);

    
private:
    int nextTemp = 1;
    
    
    std::string currentTempName() const;
    
    void emitLine(const std::string &text) const;
    std::string generateNodeCode(const Node &node);
    void releaseTemp(const Node &node);

    void generateExpressionCode(const Node &node);
    void generateOperatorCode(const Node &node);
    void generateFunctionCallCode(const Node &node);
};
