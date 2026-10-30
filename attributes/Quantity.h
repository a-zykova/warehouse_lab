#pragma once

class Quantity {
private:
    int value_;
public:
    explicit Quantity(int val);
    int getValue() const;
    void setValue(int val);
    void change(int delta);
};