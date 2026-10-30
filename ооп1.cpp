#include <iostream>
#include "Product.h"
#include "Warehouse.h"
#include "Factories.h"

int Product::nextId_ = 1;

int main() {
    try {
        std::cout << "=== Stage 4: Factories and Iterators ===" << std::endl;

        Warehouse myWarehouse(5);

        SmartphoneFactory phoneFactory;
        MilkFactory milkFactory;
        LaptopFactory laptopFactory;

        myWarehouse.addProduct(phoneFactory.createProduct(0, "iPhone 15", 1000, 10, 0.2));
        myWarehouse.addProduct(milkFactory.createProduct(0, "Milk 3.2%", 80, 50, 1.0));
        myWarehouse.addProduct(laptopFactory.createProduct(0, "MacBook Pro", 2500, 5, 1.5));

        std::cout << "\n--- 1. Iterating over Warehouse (Non-const) ---" << std::endl;
        for (const auto& p : myWarehouse) {
            p->printInfo();
        }

        std::cout << "\n--- 2. Iterating with Const Iterator ---" << std::endl;
        const Warehouse& constRef = myWarehouse; // Делаем константную ссылку
        for (const auto& p : constRef) {
            p->printInfo(); // Работает благодаря ConstWarehouseIterator
        }

        std::cout << "\n--- 3. Testing Copy Constructor (Rule of Five) ---" << std::endl;
        Warehouse copyWarehouse = myWarehouse;
        std::cout << "Original size: " << myWarehouse.size()
            << ", Copy size: " << copyWarehouse.size() << std::endl;

        std::cout << "\n--- 4. Testing findById ---" << std::endl;
        Product* found = myWarehouse.findById(2);
        if (found) {
            std::cout << "Found product: ";
            found->printInfo();
        }

        std::cout << "\n--- 5. Testing transferTo ---" << std::endl;
        Product* toTransfer = myWarehouse.findById(3);
        if (toTransfer) {
            toTransfer->transferTo(copyWarehouse);
            std::cout << "Product 3 transferred to copy warehouse." << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.get(); // Чтобы консоль не закрывалась сразу

    return 0;
}