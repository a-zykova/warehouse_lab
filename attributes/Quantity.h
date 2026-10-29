#pragma once
#include <stdexcept>

class Quantity {
private:
    int value_;
public:
    explicit Quantity(int val) : value_(val) {
        if (val < 0) throw std::invalid_argument("Quantity cannot be negative");
    }
    int getValue() const { return value_; }
    void setValue(int val) {
        if (val < 0) throw std::invalid_argument("Quantity cannot be negative");
        value_ = val;
    }
    // Реализация метода change
    void change(int delta) {
        int newVal = value_ + delta;
        if (newVal < 0) throw std::invalid_argument("Quantity cannot be less than zero");
        value_ = newVal;
    }
};