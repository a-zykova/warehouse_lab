#include "Product.h"
#include "Warehouse.h" 
#include <iostream>


int Product::nextId_ = 1;

Product::Product(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight, const std::string& category)
    : id(nextId_++), name(name), price_(price), quantity_(quantity), weight_(weight), category(category) {
}
void Product::changeQuantity(int delta) {
    quantity_.change(delta);
}

void Product::setPrice(const Price& newPrice) {
    price_ = newPrice;
}

void Product::transferTo(Warehouse& other) {
    other.addProduct(this->clone()); 
    this->changeQuantity(-this->getQuantity().getValue()); 
}


void Product::printInfo() const {
    std::cout << "[" << category << "] ID: " << id << " | " << name
        << " | Price: " << price_.getValue()
        << " | Qty: " << quantity_.getValue()
        << " | Weight: " << weight_.getValue() << "kg" << std::endl;
}