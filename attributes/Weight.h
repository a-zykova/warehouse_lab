#pragma once
#include <stdexcept>

class Weight {
private:
    double value_;
public:
    //  Валидация для double
    explicit Weight(double val) : value_(val) {
        if (val < 0) throw std::invalid_argument("Weight cannot be negative");
    }
    double getValue() const { return value_; }
    void setValue(double val) {
        if (val < 0) throw std::invalid_argument("Weight cannot be negative");
        value_ = val;
    }
};