#include <iostream>
#include <string>
#include  <fstream>
#include <sstream>
#include "lexer.hpp"



std::string readFile(const std::string &filename) {
    std::stringstream fileContent;

    std::ifstream file(filename);
    if(file.is_open()) {
        fileContent << file.rdbuf();
    } else {
        std::cerr << "Could not open file " << filename << "!\n";
        exit(1);
    }

    return fileContent.str();
}


int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cout << "Usage: ./unfold <FILENAME>\n";
        return 1;
    }

    // Get the expression
    std::string expression = readFile(std::string(argv[1]));

    std::cout << "expression: " << expression << "\n";

    // Create tokens from the input
    std::vector<Token> tokens;
    tokenize(expression, tokens);

    for(const Token &token : tokens) {
        std::string tokenType;
        switch(token.type) {
            case Token::Type::WHITESPACE:
                tokenType = "whitespace";
                break;
            case Token::Type::ADDITION:
                tokenType = "addition";
                break;
            case Token::Type::SUBTRACTION:
                tokenType = "subtraction";
                break;
            case Token::Type::MULTIPLICATION:
                tokenType = "multiplication";
                break;
            case Token::Type::DIVISION:
                tokenType = "division";
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
