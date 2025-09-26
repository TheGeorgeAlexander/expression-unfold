#pragma once

#include "lexer.hpp"
#include <vector>
#include <string>



class Node {
public:
    Node();
    Node(const Token token);

    std::vector<Node> children;

    std::string getValue() const;
    Token::Type getType() const;
    

private:
    Token token;
};
