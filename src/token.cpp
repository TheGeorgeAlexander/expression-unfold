#include "token.hpp"
#include <string>



Token::Token(Token::Type type, const std::string &value, std::size_t line, std::size_t column)
    : type(type), value(value), line(line), column(column) { }

