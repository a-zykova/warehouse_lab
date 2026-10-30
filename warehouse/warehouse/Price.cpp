#include "Price.h"
#include <stdexcept>

Price::Price(int val) : value_(val) {
    if (val < 0) throw std::invalid_argument("Price cannot be negative");
}

int Price::getValue() const {
    return value_;
}

void Price::setValue(int val) {
    if (val < 0) throw std::invalid_argument("Price cannot be negative");
    value_ = val;
}