#include "lexer.hpp"
#include <utility>
#include <regex>
#include <vector>
#include <string_view>
#include <iostream>



Token::Token(Token::Type type, const std::string &value, std::size_t line, std::size_t column)
    : type(type), value(value), line(line), column(column) { }


std::pair<std::regex, Token::Type> createTokenDefinition(std::string const &regex, Token::Type const type) {
    return std::make_pair(std::regex("^" + regex, std::regex_constants::icase), type);
}


void tokenize(const std::string &text, std::vector<Token> &tokens) {
    std::pair<std::regex, Token::Type> TOKEN_DEFINITIONS[] = {
        createTokenDefinition(R"(\s+)",           Token::Type::WHITESPACE),
        createTokenDefinition(R"([+-*/])",        Token::Type::OPERATOR),
        createTokenDefinition(R"(\()",            Token::Type::BRACKET_OPEN),
        createTokenDefinition(R"(\))",            Token::Type::BRACKET_CLOSE),
        createTokenDefinition(R"(,)",             Token::Type::COMMA),
        createTokenDefinition(R"(\d+(?:\.\d+)?)", Token::Type::NUMBER),
        createTokenDefinition(R"([a-z_]\w*)",     Token::Type::IDENTIFIER)
    };

    std::size_t line = 1, column = 1, pos = 0;
    std::string_view input = text;

    // Go through the whole input text
    while(pos < input.size()) {
        bool matched = false;
        std::string_view current = input.substr(pos);

        // Go through all token definitions to see what matches next
        for(const std::pair<std::regex, Token::Type> &def : TOKEN_DEFINITIONS) {
            std::cmatch match;

            // Match!
            if(std::regex_search(current.begin(), current.end(), match, def.first)) {
                matched = true;
                const std::string matchStr = match.str(0);
                const Token::Type type = def.second;

                // Whitespace might span multiple lines
                if(type == Token::Type::WHITESPACE) {
                    for(char c : matchStr) {
                        if(c == '\n') {
                            line++;
                            column = 1;
                        } else {
                            column++;
                        }
                    }

                // the rest doesn't
                } else {
                    tokens.emplace_back(type, matchStr, line, column);
                    column += match.length();
                }

                pos += match.length();
                break;
            }
        }

        // Nothing matched? Error!
        if(!matched) {
            throw std::runtime_error("Unknown token at line " + std::to_string(line) + ", column " + std::to_string(column));
        }
    }
}
