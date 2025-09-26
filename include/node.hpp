#pragma once

#include "lexer.hpp"



class Node {
public:
    Node();
    Node(const Token token);

    std::vector<Node> children;

    Token getToken() const;
    

private:
    Token token;
};
