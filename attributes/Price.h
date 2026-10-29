#pragma once
#include <stdexcept>

class Price {
private:
    int value_;
public:
    //  Реализация конструктора с валидацией
    explicit Price(int val) : value_(val) {
        if (val < 0) throw std::invalid_argument("Price cannot be negative");
    }
    int getValue() const { return value_; }
    void setValue(int val) {
        if (val < 0) throw std::invalid_argument("Price cannot be negative");
        value_ = val;
    }
};