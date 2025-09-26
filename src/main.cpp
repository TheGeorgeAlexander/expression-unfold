#include <iostream>
#include <string>
#include  <fstream>
#include "lexer.hpp"



std::string readFile(const std::string& filename) {
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
    } else if(argc == 2) {
        expression = readFile(std::string(argv[1]));
    } else {
        std::cout << "Two options:\n";
        std::cout << "  ./unfold             Manually enter an expression.\n";
        std::cout << "  ./unfold <FILENAME>  Automatically read the expression from a text file.\n";
        return 1;
    }

    // Create tokens from the input
    std::vector<Token> tokens;
    tokenize(expression, tokens);

    for(const Token &token : tokens) {
        std::string tokenType;
        switch(token.type) {
            case Token::Type::WHITESPACE:
                tokenType = "whitespace";
                break;
            case Token::Type::OPERATOR:
                tokenType = "operator";
                break;
            case Token::Type::BRACKET_OPEN:
                tokenType = "bracket open";
                break;
            case Token::Type::BRACKET_CLOSE:
                tokenType = "bracket close";
                break;
            case Token::Type::COMMA:
                tokenType = "comma";
                break;
            case Token::Type::NUMBER:
                tokenType = "number";
                break;
            case Token::Type::IDENTIFIER:
                tokenType = "identifier";
                break;
            
            default:
                tokenType = "unknown";
                break;
        }
        std::cout << tokenType << " '" << token.value << "' at line " << token.line << ", column " << token.column << "\n";
    }

    // Parse the tokens into a tree
    // TODO: ^^

    // Walk through the tree and output the code
    // TODO: ^^
    return 0;
}
