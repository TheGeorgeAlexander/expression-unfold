#include "codegen.hpp"
#include "node.hpp"
#include <iostream>



void CodeGenerator::generateCode(const Node &root) {
    if(root.children.empty()) {
        emitLine(root.getValue());
    } else {
        generateExpressionCode(root);
    }
}


std::string CodeGenerator::currentTempName() const {
    if(nextTemp == 1) {
        return "result";
    }
    return "temp" + std::to_string(nextTemp - 1);
}


void CodeGenerator::emitLine(const std::string &text) const {
    std::cout << currentTempName() << " = " << text << "\n";
}


std::string CodeGenerator::generateNodeCode(const Node &node) {
    if(node.children.empty()) {
        return node.getValue();
    }

    generateExpressionCode(node);

    std::string name = currentTempName();
    nextTemp++;
    return name;
}


void CodeGenerator::releaseTemp(const Node &node) {
    if(!node.children.empty()) {
        nextTemp--;
    }
}


void CodeGenerator::generateExpressionCode(const Node &node) {
    switch(node.getType()) {
        case Token::Type::OPERATOR:
            generateOperatorCode(node);
            break;

        case Token::Type::IDENTIFIER:
            generateFunctionCallCode(node);
            break;
            
        default:
            std::cout << "UNKNOWN EXPRESSION\n";
            break;
    }
}


void CodeGenerator::generateOperatorCode(const Node &node) {
    std::string leftHandSide = generateNodeCode(node.children[0]);
    std::string rightHandSide = generateNodeCode(node.children[1]);
    releaseTemp(node.children[0]);
    releaseTemp(node.children[1]);

    emitLine(leftHandSide + " " + node.getValue() + " " + rightHandSide);

}


void CodeGenerator::generateFunctionCallCode(const Node &node) {
    std::string parameterTemps;
    int originalTemp = nextTemp;
    for(const Node &child : node.children) {
        parameterTemps += generateNodeCode(child) + ", ";
    }
    nextTemp = originalTemp;
    emitLine(node.getValue() + "(" + parameterTemps.substr(0, parameterTemps.length() - 2) + ")");
}
