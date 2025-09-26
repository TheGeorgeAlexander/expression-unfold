#include "iterator.hpp"



TokenIterator::TokenIterator(const std::vector<Token> &arr)
    : array(arr) { }


Token TokenIterator::previous() const {
    errorIfOutOfBounds(-1, "previous");
    return array[index - 1];
}


Token TokenIterator::lookAhead(const std::size_t distance) const {
    errorIfOutOfBounds(distance - 1, "lookAhead");
    return array[index + (distance - 1)];
}


Token TokenIterator::next() {
    errorIfOutOfBounds(0, "next");
    index++;
    return array[index - 1];
}


void TokenIterator::errorIfOutOfBounds(const int indexOffset, const std::string &name) const {
    std::size_t newIndex = index + indexOffset;
    if(newIndex < 0 || newIndex >= array.size()) {
        throw std::runtime_error("Token iterator out of bounds trying to get " + name);
    }
}
