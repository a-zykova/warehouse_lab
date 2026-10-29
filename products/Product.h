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

    // ID генерируется автоматически
    Product(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight, const std::string& category)
        : id(nextId_++), name(name), price_(price), quantity_(quantity), weight_(weight), category(category) {
    }

    virtual ~Product() = default;

    virtual std::unique_ptr<Product> clone() const = 0;

    // Геттеры (реализация)
    int getId() const { return id; }
    std::string getName() const { return name; }
    Price getPrice() const { return price_; }
    Quantity getQuantity() const { return quantity_; }
    Weight getWeight() const { return weight_; }
    std::string getCategory() const { return category; }

    //Реализация сеттеров и действий
    void setPrice(const Price& newPrice) {
        price_ = newPrice;
    }

    void changeQuantity(int delta) {
        quantity_.change(delta);
    }

    virtual void transferTo(Warehouse& other);

    virtual void printInfo() const {
        std::cout << "[" << category << "] ID: " << id << " | " << name
            << " | Price: " << price_.getValue()
            << " | Qty: " << quantity_.getValue()
            << " | Weight: " << weight_.getValue() << "kg" << std::endl;
    }
};

// --- Промежуточные категории ---
class Electronics : public Product {
public:
    Electronics(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
        : Product(name, price, quantity, weight, "electronics") {
    }
};

class Clothing : public Product {
public:
    Clothing(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
        : Product(name, price, quantity, weight, "clothing") {
    }
};

class Food : public Product {
public:
    Food(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
        : Product(name, price, quantity, weight, "food") {
    }
};

// --- Конкретные классы с реализацией clone() ---
class Smartphone : public Electronics {
public:
    Smartphone(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
        : Electronics(name, price, quantity, weight) {
    }
    std::unique_ptr<Product> clone() const override {
        return std::make_unique<Smartphone>(*this); // [ЭТАП 2] Клонирование
    }
};

class Laptop : public Electronics {
public:
    Laptop(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
        : Electronics(name, price, quantity, weight) {
    }
    std::unique_ptr<Product> clone() const override {
        return std::make_unique<Laptop>(*this);
    }
};

class TShirt : public Clothing {
public:
    TShirt(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
        : Clothing(name, price, quantity, weight) {
    }
    std::unique_ptr<Product> clone() const override {
        return std::make_unique<TShirt>(*this);
    }
};

class Jacket : public Clothing {
public:
    Jacket(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
        : Clothing(name, price, quantity, weight) {
    }
    std::unique_ptr<Product> clone() const override {
        return std::make_unique<Jacket>(*this);
    }
};

class Milk : public Food {
public:
    Milk(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
        : Food(name, price, quantity, weight) {
    }
    std::unique_ptr<Product> clone() const override {
        return std::make_unique<Milk>(*this);
    }
};

class Bread : public Food {
public:
    Bread(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight)
        : Food(name, price, quantity, weight) {
    }
    std::unique_ptr<Product> clone() const override {
        return std::make_unique<Bread>(*this);
    }
};