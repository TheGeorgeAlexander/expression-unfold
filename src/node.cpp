#include "node.hpp"
#include "lexer.hpp"
#include <string>



Node::Node() 
    : token(Token::Type::WHITESPACE, "", 0, 0) { }


Node::Node(const Token token)
    : token(token) { }


std::string Node::getValue() const {
    return token.value;
}


Token::Type Node::getType() const {
    return token.type;
}
