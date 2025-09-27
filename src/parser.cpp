#include "parser.hpp"
#include <vector>
#include "node.hpp"
#include "token.hpp"
#include <stdexcept>



Parser::Parser(const std::vector<Token> &tokens)
    : iterator(tokens) { }


Node Parser::parse() {
    Node root = parseExpression();
    iterator.matchOrError(Token::Type::END_OF_INPUT);
    return root;
}


Node Parser::parseExpression() {
    Node expressionNode = parseTerm();

    while(iterator.check(Token::Type::OPERATOR, "+") || iterator.check(Token::Type::OPERATOR, "-")) {
        Node leftHandSide = expressionNode;
        expressionNode = Node(iterator.next());
        expressionNode.children.push_back(leftHandSide);
        expressionNode.children.push_back(parseTerm());
    }

    return expressionNode;
}


Node Parser::parseTerm() {
    Node termNode = parseFactor();

    while(iterator.check(Token::Type::OPERATOR, "*") || iterator.check(Token::Type::OPERATOR, "/")) {
        Node leftHandSide = termNode;
        termNode = Node(iterator.next());
        termNode.children.push_back(leftHandSide);
        termNode.children.push_back(parseFactor());
    }

    return termNode;
}


Node Parser::parseFactor() {
    // An expression in brackets
    if(iterator.match(Token::Type::BRACKET_OPEN)) {
        Node expression = parseExpression();
        iterator.matchOrError(Token::Type::BRACKET_CLOSE);
        return expression;
    }

    // A variable or function call
    if(iterator.check(Token::Type::IDENTIFIER)) {
        if(iterator.lookAhead(2).type == Token::Type::BRACKET_OPEN) {
            return parseFunctionCall();
        } else {
            return Node(iterator.next());
        }
    }

    // A number
    bool negativeNum = iterator.match(Token::Type::OPERATOR, "-");
    Token number = iterator.matchOrError(Token::Type::NUMBER);
    if(negativeNum) {
        number.value = "-" + number.value;
    }
    return Node(number);
}


Node Parser::parseFunctionCall() {
    Node functionNode = Node(iterator.next());
    iterator.next(); // Bracket open

    functionNode.children.push_back(parseExpression());
    while(iterator.match(Token::Type::COMMA)) {
        functionNode.children.push_back(parseExpression());
    }
    iterator.matchOrError(Token::Type::BRACKET_CLOSE);

    return functionNode;
}
