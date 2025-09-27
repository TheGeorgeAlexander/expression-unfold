#include "iterator.hpp"
#include <vector>
#include "token.hpp"
#include <stdexcept>



TokenIterator::TokenIterator(const std::vector<Token> &arr)
    : array(arr) { }


Token TokenIterator::lookBehind() const {
    if(index == 0) {
        throw std::runtime_error("Token iterator can't lookBehind() when at the first token.");
    }
    return array[index - 1];
}


Token TokenIterator::lookAhead(const std::size_t distance) const {
    if(index + (distance - 1) >= array.size()) {
        return array.back();
    }
    return array[index + (distance - 1)];
}


Token TokenIterator::next() {
    if(isAtEnd()) {
        return array.back();
    }
    index++;
    return array[index - 1];
}


bool TokenIterator::isAtEnd() {
    return index >= array.size();
}


bool TokenIterator::match(Token::Type type, const std::string &value) {
    if(check(type, value)) {
        next();
        return true;
    }
    return false;
}


Token TokenIterator::matchOrError(const Token::Type type, const std::string &value) {
    Token token = lookAhead();
    if(!match(type, value)) {
        throw std::runtime_error("Expected " + Token::typeString(type) + " at " + Token::locationString(token) + " but got " + Token::typeString(token.type));
    }
    return token;
}


bool TokenIterator::check(Token::Type type, const std::string &value) {
    if(isAtEnd()) {
        return false;
    }

    const Token &token = lookAhead();
    if(token.type != type || (!value.empty() && token.value != value)) {
        return false;
    }
    return true;
}

