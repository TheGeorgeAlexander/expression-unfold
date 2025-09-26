#include "parser.hpp"
#include <vector>
#include "lexer.hpp"



Parser::Parser(const std::vector<Token> &tokens)
    : iterator(tokens) { }


Node Parser::parse() {
    return parseExpression();
}


Node Parser::parseExpression() {
    Node expressionNode = parseTerm();

    while(!iterator.isAtEnd() && iterator.lookAhead().type == Token::Type::OPERATOR) {
        Node leftHandSide = expressionNode;
        expressionNode = Node(iterator.next());
        expressionNode.children.push_back(leftHandSide);
        expressionNode.children.push_back(parseExpression());
    }

    return expressionNode;
}


Node Parser::parseTerm() {
    Token::Type lookAheadType = iterator.lookAhead().type;

    // An expression in brackets
    if(lookAheadType == Token::Type::BRACKET_OPEN) {
        iterator.next();
        Node expression = parseExpression();
        if(iterator.next().type != Token::Type::BRACKET_CLOSE) {
            throw std::runtime_error("Expected closing bracket at " + tokenLocString(iterator.previous()));
        }
        return expression;
    }

    // A variable or function call
    if(lookAheadType == Token::Type::IDENTIFIER) {
        if(iterator.lookAhead(2).type == Token::Type::BRACKET_OPEN) {
            return parseFunctionCall();
        } else {
            return Node(iterator.next());
        }
    }

    // A number
    if(lookAheadType == Token::Type::NUMBER) {
        return Node(iterator.next());
    }

    throw std::runtime_error("Expected term at " + tokenLocString(iterator.next()));
}


Node Parser::parseFunctionCall() {
    Node functionNode = Node(iterator.next());
    iterator.next(); // Bracket open

    functionNode.children.push_back(parseExpression());
    while(iterator.lookAhead().type == Token::Type::COMMA) {
        iterator.next();
        functionNode.children.push_back(parseExpression());
    }

    if(iterator.next().type != Token::Type::BRACKET_CLOSE) {
        throw std::runtime_error("Expected closing bracket at " + tokenLocString(iterator.previous()));
    }

    return functionNode;
}


std::string Parser::tokenLocString(const Token token) {
    return "line " + std::to_string(token.line) + ", column " + std::to_string(token.column);
}
