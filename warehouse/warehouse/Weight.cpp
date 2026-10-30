#include "Weight.h"
#include <stdexcept>

Weight::Weight(double val) : value_(val) {
    if (val < 0) throw std::invalid_argument("Weight cannot be negative");
}

double Weight::getValue() const {
    return value_;
}

void Weight::setValue(double val) {
    if (val < 0) throw std::invalid_argument("Weight cannot be negative");
    value_ = val;
}