#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "Price.h"
#include "Quantity.h"
#include "Weight.h"

class Warehouse;

class Product {
protected:
    int id;
    std::string name;
    Price price_;
    Quantity quantity_;
    Weight weight_;
    std::string category;

public:
    static int nextId_;

    // Объявление конструктора
    Product(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight, const std::string& category);

    virtual ~Product() = default;

    virtual std::unique_ptr<Product> clone() const = 0;

    int getId() const { return id; }
    std::string getName() const { return name; }
    Price getPrice() const { return price_; }
    Quantity getQuantity() const { return quantity_; }
    Weight getWeight() const { return weight_; }
    std::string getCategory() const { return category; }

    
    void changeQuantity(int delta);
    void setPrice(const Price& newPrice);
    virtual void transferTo(Warehouse& other);
    virtual void printInfo() const;
};