#pragma once

#include <string>
#include <vector>
#include <utility>
#include <regex>


class Token {
public:
    enum class Type {
        WHITESPACE,
        OPERATOR,
        BRACKET_OPEN,
        BRACKET_CLOSE,
        COMMA,
        NUMBER,
        IDENTIFIER
    } type;
    std::string value;
    std::size_t line;
    std::size_t column;

    Token(Token::Type type, const std::string &value, std::size_t line, std::size_t column);
};


std::pair<std::regex, Token::Type> createTokenDefinition(const std::string &regex, const Token::Type type);


void tokenize(const std::string &text, std::vector<Token> &tokens);
