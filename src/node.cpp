#include "node.hpp"
#include "lexer.hpp"



Node::Node() 
    : token(Token::Type::WHITESPACE, "", 0, 0) { }


Node::Node(const Token token)
    : token(token) { }


Token Node::getToken() const {
    return token;
}
