#include <iostream>
#include "Product.h"
#include "Factories.h"
#include "Warehouse.h"

// Обязательно инициализируем статическую переменную (вне класса!)
int Product::nextId_ = 1;
int main() {
    try {
        std::cout << "=== Stage 3: Warehouse and Factories ===" << std::endl;

        // 1. Создаем склад на 5 мест
        Warehouse myWarehouse(5);

        // 2. Создаем фабрики
        SmartphoneFactory phoneFactory;
        MilkFactory milkFactory;

        // 3. Добавляем товары через фабрики
        myWarehouse.addProduct(phoneFactory.createProduct("iPhone", 1000, 10, 0.2));
        myWarehouse.addProduct(milkFactory.createProduct("Milk", 80, 50, 1.0));

        // 4. Проверяем Итератор (цикл for)
        std::cout << "\n--- Products in Warehouse ---" << std::endl;
        for (const auto& p : myWarehouse) {
            p->printInfo();
        }

        // 5. Проверяем копирование (Правило пяти)
        std::cout << "\n--- Copying Warehouse ---" << std::endl;
        Warehouse copyWarehouse = myWarehouse;
        std::cout << "Copy size: " << copyWarehouse.size() << std::endl;

        // 6. Проверяем поиск
        std::cout << "\n--- Searching by ID ---" << std::endl;
        Product* found = myWarehouse.findById(1);
        if (found) found->printInfo();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}