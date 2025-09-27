#pragma once

#include <string>



class Token {
public:
    enum class Type {
        WHITESPACE,
        OPERATOR,
        BRACKET_OPEN,
        BRACKET_CLOSE,
        COMMA,
        NUMBER,
        IDENTIFIER,
        END_OF_INPUT
    } type;
    std::string value;
    std::size_t line;
    std::size_t column;

    Token(Token::Type type, const std::string &value, std::size_t line, std::size_t column);


    static std::string typeString(const Token::Type type) {
        switch(type) {
            case Token::Type::WHITESPACE:
                return "whitespace";

            case Token::Type::OPERATOR:
                return "operator";

            case Token::Type::BRACKET_OPEN:
                return "opening bracket";

            case Token::Type::BRACKET_CLOSE:
                return "closing bracket";

            case Token::Type::COMMA:
                return "comma";

            case Token::Type::NUMBER:
                return "number";

            case Token::Type::IDENTIFIER:
                return "identifier";

            case Token::Type::END_OF_INPUT:
                return "end of input";

            default:
                return "UNKNOWN TOKEN TYPE";
        }
    }


    static std::string locationString(const Token token) {
        return "line " + std::to_string(token.line) + ", column " + std::to_string(token.column);
    }
};