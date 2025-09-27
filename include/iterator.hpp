#pragma once

#include <vector>
#include "token.hpp"



class TokenIterator {
public:
    TokenIterator(const std::vector<Token> &arr);

    Token lookBehind() const;
    Token lookAhead(const std::size_t distance = 1) const;
    Token next();
    bool isAtEnd();

    bool match(Token::Type type, const std::string &value = "");
    bool check(Token::Type type, const std::string &value = "");


private:
    const std::vector<Token> array;
    std::size_t index = 0;
};
