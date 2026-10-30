#include "Products.h"

Electronics::Electronics(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
    : Product(name, price, quantity, weight, "electronics") {
}

Clothing::Clothing(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
    : Product(name, price, quantity, weight, "clothing") {
}

Food::Food(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
    : Product(name, price, quantity, weight, "food") {
}

Smartphone::Smartphone(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
    : Electronics(name, price, quantity, weight) {
}

std::unique_ptr<Product> Smartphone::clone() const {
    return std::make_unique<Smartphone>(*this);
}

Laptop::Laptop(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
    : Electronics(name, price, quantity, weight) {
}

std::unique_ptr<Product> Laptop::clone() const {
    return std::make_unique<Laptop>(*this);
}

TShirt::TShirt(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
    : Clothing(name, price, quantity, weight) {
}

std::unique_ptr<Product> TShirt::clone() const {
    return std::make_unique<TShirt>(*this);
}

Jacket::Jacket(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
    : Clothing(name, price, quantity, weight) {
}

std::unique_ptr<Product> Jacket::clone() const {
    return std::make_unique<Jacket>(*this);
}

Milk::Milk(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
    : Food(name, price, quantity, weight) {
}

std::unique_ptr<Product> Milk::clone() const {
    return std::make_unique<Milk>(*this);
}

Bread::Bread(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
    : Food(name, price, quantity, weight) {
}

std::unique_ptr<Product> Bread::clone() const {
    return std::make_unique<Bread>(*this);
}