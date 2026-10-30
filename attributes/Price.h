#pragma once

class Price {
private:
    int value_;
public:
    explicit Price(int val);
    int getValue() const;
    void setValue(int val);
};