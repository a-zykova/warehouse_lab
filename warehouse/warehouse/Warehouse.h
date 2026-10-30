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
    std::vector<std::unique_ptr<Product>> products_;
    size_t maxSize_;

public:
   
    explicit Warehouse(size_t maxSize) : maxSize_(maxSize) {
        if (maxSize == 0) throw std::invalid_argument("Max size must be positive");
    }

    ~Warehouse() = default;

    Warehouse(const Warehouse& other) : maxSize_(other.maxSize_) {
        for (const auto& p : other.products_) {
            products_.push_back(p->clone());
        }
    }

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

    Warehouse(Warehouse&& other) noexcept
        : products_(std::move(other.products_)), maxSize_(other.maxSize_) {
        other.maxSize_ = 0;
    }

    Warehouse& operator=(Warehouse&& other) noexcept {
        if (this != &other) {
            products_ = std::move(other.products_);
            maxSize_ = other.maxSize_;
            other.maxSize_ = 0;
        }
        return *this;
    }


    void addProduct(std::unique_ptr<Product> product) {
        if (products_.size() >= maxSize_) {
            throw std::overflow_error("Warehouse is full!");
        }
        products_.push_back(std::move(product));
    }

    void removeById(int id) {
        auto it = std::remove_if(products_.begin(), products_.end(),
            [id](const std::unique_ptr<Product>& p) { return p->getId() == id; });
        if (it != products_.end()) products_.erase(it, products_.end());
    }

    void removeByIndex(size_t index) {
        if (index >= products_.size()) throw std::out_of_range("Index out of range");
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
            if (p->getCategory() == category) result.push_back(p.get());
        }
        return result;
    }

    std::vector<Product*> findByPrice(const Price& price) const {
        std::vector<Product*> result;
        for (const auto& p : products_) {
            if (p->getPrice().getValue() == price.getValue()) result.push_back(p.get());
        }
        return result;
    }

    size_t size() const { return products_.size(); }

    class WarehouseIterator {
    private:
        std::vector<std::unique_ptr<Product>>::iterator current_;
        std::vector<std::unique_ptr<Product>>::iterator end_;

    public:
        WarehouseIterator(std::vector<std::unique_ptr<Product>>::iterator current, std::vector<std::unique_ptr<Product>>::iterator end)
            : current_(current), end_(end) {
        }

        Product* operator*() const { return current_->get(); }

        WarehouseIterator& operator++() { ++current_; return *this; }

        bool operator!=(const WarehouseIterator& other) const { return current_ != other.current_; }

        bool operator==(const WarehouseIterator& other) const { return current_ == other.current_; }
    };

    WarehouseIterator begin() { return WarehouseIterator(products_.begin(), products_.end()); }
    WarehouseIterator end() { return WarehouseIterator(products_.end(), products_.end()); }

    class ConstWarehouseIterator {
    private:
        std::vector<std::unique_ptr<Product>>::const_iterator current_;
    public:
        ConstWarehouseIterator(std::vector<std::unique_ptr<Product>>::const_iterator current) : current_(current) {}
        const Product* operator*() const { return current_->get(); }
        ConstWarehouseIterator& operator++() { ++current_; return *this; }
        bool operator!=(const ConstWarehouseIterator& other) const { return current_ != other.current_; }
    };

    ConstWarehouseIterator begin() const { return ConstWarehouseIterator(products_.cbegin()); }
    ConstWarehouseIterator end() const { return ConstWarehouseIterator(products_.cend()); }
};

inline void Product::transferTo(Warehouse& other) {
    other.addProduct(this->clone());
    this->changeQuantity(-this->getQuantity().getValue());
}