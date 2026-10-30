#pragma once
#include <memory>
#include <string>
#include "Product.h"

// Абстрактный класс ProductFactory с чисто виртуальным методом createProduct
class ProductFactory {
public:
    virtual ~ProductFactory() = default;
    virtual std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) = 0;
};

// SmartphoneFactory
class SmartphoneFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override {
        return std::make_unique<Smartphone>(name, Price(price), Quantity(quantity), Weight(weight));
    }
};

//  LaptopFactory
class LaptopFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override {
        return std::make_unique<Laptop>(name, Price(price), Quantity(quantity), Weight(weight));
    }
};

// TShirtFactory
class TShirtFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override {
        return std::make_unique<TShirt>(name, Price(price), Quantity(quantity), Weight(weight));
    }
};

// JacketFactory
class JacketFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override {
        return std::make_unique<Jacket>(name, Price(price), Quantity(quantity), Weight(weight));
    }
};

// MilkFactory
class MilkFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override {
        return std::make_unique<Milk>(name, Price(price), Quantity(quantity), Weight(weight));
    }
};

// BreadFactory
class BreadFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override {
        return std::make_unique<Bread>(name, Price(price), Quantity(quantity), Weight(weight));
    }
};