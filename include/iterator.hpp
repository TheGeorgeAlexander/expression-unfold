#pragma once

#include <vector>
#include "lexer.hpp"



class TokenIterator {
public:
    TokenIterator(const std::vector<Token> &arr);

    Token previous() const;
    Token lookAhead(const std::size_t distance = 1) const;
    Token next();
    bool isAtEnd();


private:
    const std::vector<Token> array;
    std::size_t index = 0;

    void errorIfOutOfBounds(const int indexOffset, const std::string &name) const;
};
