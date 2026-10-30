#pragma once

class Weight {
private:
    double value_;
public:
    explicit Weight(double val);
    double getValue() const;
    void setValue(double val);
};