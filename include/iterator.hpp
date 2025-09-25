#pragma once

#include <vector>
#include "lexer.hpp"



class TokenIterator {
public:
    TokenIterator(const std::vector<Token> &arr);

    Token previous();
    Token lookAhead();
    Token next();


private:
    std::vector<Token> array;
    std::size_t index = 0;
};
