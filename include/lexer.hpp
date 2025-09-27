#pragma once

#include <utility>
#include <regex>
#include "token.hpp"
#include <vector>



std::pair<std::regex, Token::Type> createTokenDefinition(const std::string &regex, const Token::Type type);


void tokenize(const std::string &text, std::vector<Token> &tokens);
