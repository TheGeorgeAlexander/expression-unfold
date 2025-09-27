#pragma once

#include "iterator.hpp"
#include "lexer.hpp"
#include "node.hpp"


class Parser {
public:
    Parser(const std::vector<Token> &tokens);

    Node parse();


private:
    TokenIterator iterator;

    Node parseExpression();
    Node parseTerm();
    Node parseFactor();
    Node parseFunctionCall();

    std::string tokenLocString(const Token token);
};
