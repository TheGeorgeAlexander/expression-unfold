#pragma once

#include <vector>
#include "token.hpp"
#include "node.hpp"
#include "iterator.hpp"


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
};
