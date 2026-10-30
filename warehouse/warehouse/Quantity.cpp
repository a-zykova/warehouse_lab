#include "Quantity.h"
#include <stdexcept>

Quantity::Quantity(int val) : value_(val) {
    if (val < 0) throw std::invalid_argument("Quantity cannot be negative");
}

int Quantity::getValue() const {
    return value_;
}

void Quantity::setValue(int val) {
    if (val < 0) throw std::invalid_argument("Quantity cannot be negative");
    value_ = val;
}

void Quantity::change(int delta) {
    int newVal = value_ + delta;
    if (newVal < 0) throw std::invalid_argument("Quantity cannot be less than zero");
    value_ = newVal;
}