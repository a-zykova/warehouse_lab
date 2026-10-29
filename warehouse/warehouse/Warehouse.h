#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "Product.h"

class Warehouse {
private:
    //  ѕол€ класса
    std::vector<std::unique_ptr<Product>> products_;
    size_t maxSize_;

public:
    //   онструктор с проверкой на положительный размер
    explicit Warehouse(size_t maxSize) : maxSize_(maxSize) {
        if (maxSize == 0) {
            throw std::invalid_argument("Max size must be positive");
        }
    }

    //   онструктор копировани€ (глубокое копирование через clone)
    Warehouse(const Warehouse& other) : maxSize_(other.maxSize_) {
        for (const auto& p : other.products_) {
            products_.push_back(p->clone());
        }
    }

    //  ќператор присваивани€ копированием (с проверкой на самоприсваивание)
    Warehouse& operator=(const Warehouse& other) {
        if (this != &other) {
            maxSize_ = other.maxSize_;
            products_.clear();
            for (const auto& p : other.products_) {
                products_.push_back(p->clone());
            }
        }
        return *this;
    }

    //  онструктор перемещени€ (noexcept)
    Warehouse(Warehouse&& other) noexcept
        : products_(std::move(other.products_)), maxSize_(other.maxSize_) {
        other.maxSize_ = 0;
    }

    // ќператор присваивани€ перемещением 
    Warehouse& operator=(Warehouse&& other) noexcept {
        if (this != &other) {
            products_ = std::move(other.products_);
            maxSize_ = other.maxSize_;
            other.maxSize_ = 0;
        }
        return *this;
    }

    
    ~Warehouse() = default;

    void addProduct(std::unique_ptr<Product> product) {
        if (products_.size() >= maxSize_) {
            throw std::overflow_error("Warehouse is full!");
        }
        products_.push_back(std::move(product));
    }

    void removeById(int id) {
        auto it = std::remove_if(products_.begin(), products_.end(),
            [id](const std::unique_ptr<Product>& p) { return p->getId() == id; });
        if (it != products_.end()) {
            products_.erase(it, products_.end());
        }
    }

    void removeByIndex(size_t index) {
        if (index >= products_.size()) {
            throw std::out_of_range("Index out of range");
        }
        products_.erase(products_.begin() + index);
    }

    Product* findById(int id) const {
        for (const auto& p : products_) {
            if (p->getId() == id) return p.get();
        }
        return nullptr;
    }

    std::vector<Product*> findByCategory(const std::string& category) const {
        std::vector<Product*> result;
        for (const auto& p : products_) {
            if (p->getCategory() == category) {
                result.push_back(p.get());
            }
        }
        return result;
    }

    std::vector<Product*> findByPrice(const Price& price) const {
        std::vector<Product*> result;
        for (const auto& p : products_) {
            if (p->getPrice().getValue() == price.getValue()) {
                result.push_back(p.get());
            }
        }
        return result;
    }

    // ¬спомогательный метод дл€ получени€ размера
    size_t size() const { return products_.size(); }

    
    class WarehouseIterator {
    private:
        std::vector<std::unique_ptr<Product>>::iterator it;
    public:
        WarehouseIterator(std::vector<std::unique_ptr<Product>>::iterator i) : it(i) {}

        
        Product* operator*() const { return it->get(); }

        WarehouseIterator& operator++() { ++it; return *this; }

        bool operator!=(const WarehouseIterator& other) const { return it != other.it; }
    };

    WarehouseIterator begin() { return WarehouseIterator(products_.begin()); }
    WarehouseIterator end() { return WarehouseIterator(products_.end()); }
};


inline void Product::transferTo(Warehouse& other) {
    other.addProduct(this->clone()); //  лонируем товар на другой склад
    this->changeQuantity(-this->getQuantity().getValue()); // ќбнул€ем остаток здесь
}