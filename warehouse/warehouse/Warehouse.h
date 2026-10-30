#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Products.h"

class Warehouse {
private:
    std::vector<std::unique_ptr<Product>> products_;
    size_t maxSize_;

public:
    explicit Warehouse(size_t maxSize);
    ~Warehouse() = default;
    Warehouse(const Warehouse& other);
    Warehouse& operator=(const Warehouse& other);
    Warehouse(Warehouse&& other) noexcept;
    Warehouse& operator=(Warehouse&& other) noexcept;

    void addProduct(std::unique_ptr<Product> product);
    void removeById(int id);
    void removeByIndex(size_t index);
    Product* findById(int id) const;
    std::vector<Product*> findByCategory(const std::string& category) const;
    std::vector<Product*> findByPrice(const Price& price) const;
    size_t size() const { return products_.size(); }

    // Итератор (его реализацию оставляем в .h, так как это шаблонный класс по сути)
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

    WarehouseIterator begin();
    WarehouseIterator end();

    // Константный итератор
    class ConstWarehouseIterator {
    private:
        std::vector<std::unique_ptr<Product>>::const_iterator current_;
    public:
        ConstWarehouseIterator(std::vector<std::unique_ptr<Product>>::const_iterator current) : current_(current) {}
        const Product* operator*() const { return current_->get(); }
        ConstWarehouseIterator& operator++() { ++current_; return *this; }
        bool operator!=(const ConstWarehouseIterator& other) const { return current_ != other.current_; }
    };

    ConstWarehouseIterator begin() const;
    ConstWarehouseIterator end() const;
};