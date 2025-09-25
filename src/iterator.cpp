#include "iterator.hpp"



TokenIterator::TokenIterator(const std::vector<Token> &arr)
    : array(arr) { }


Token TokenIterator::previous() {
    return array[index - 1];
}


Token TokenIterator::lookAhead() {
    return array[index];
}


Token TokenIterator::next() {
    index++;
    return array[index - 1];
}
