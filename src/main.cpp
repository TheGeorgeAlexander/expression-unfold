#include <string>
#include <fstream>
#include <iostream>
#include "token.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "node.hpp"
#include "codegen.hpp"



std::string readFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}


int main(int argc, char *argv[]) {
    // Get the expression
    std::string expression;
    if(argc == 1) {
        std::cout << "Expression: ";
        getline(std::cin, expression);
        std::cout << "\n";
    } else if(argc == 2) {
        expression = readFile(std::string(argv[1]));
    } else {
        std::cout << "Two options:\n";
        std::cout << "  ./unfold             Enter an expression manually.\n";
        std::cout << "  ./unfold <FILENAME>  Read the expression from a text file.\n";
        return 1;
    }

    // Create tokens from the input
    std::vector<Token> tokens;
    tokenize(expression, tokens);

    // Parse the tokens into a tree
    Parser parser(tokens);
    Node root = parser.parse();

    // Walk through the tree and output the code
    CodeGenerator printer;
    printer.generateCode(root);
    return 0;
}
