#pragma once
#include "Product.h"

class Electronics : public Product {
public:
    Electronics(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
};

class Clothing : public Product {
public:
    Clothing(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
};

class Food : public Product {
public:
    Food(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
};

class Smartphone : public Electronics {
public:
    Smartphone(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override;
};

class Laptop : public Electronics {
public:
    Laptop(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override;
};

class TShirt : public Clothing {
public:
    TShirt(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override;
};

class Jacket : public Clothing {
public:
    Jacket(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override;
};

class Milk : public Food {
public:
    Milk(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override;
};

class Bread : public Food {
public:
    Bread(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override;
};