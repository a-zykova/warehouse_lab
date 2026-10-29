#include <iostream>
#include "Product.h"

// Обязательно инициализируем статическую переменную (вне класса!)
int Product::nextId_ = 1;

int main() {
    try {
        //  Демонстрация работы
        std::cout << "=== Stage 2 Demonstration ===" << std::endl;

        // Создаем товары (ID генерируются автоматически: 1, 2, 3...)
        Smartphone phone("iPhone 15", Price(1000), Quantity(10), Weight(0.2));
        Milk milk("Milk 3.2%", Price(80), Quantity(50), Weight(1.0));

        std::cout << "\n--- Initial Products ---" << std::endl;
        phone.printInfo();
        milk.printInfo();

        // Тестируем изменение данных
        std::cout << "\n--- Modifying Milk ---" << std::endl;
        milk.setPrice(Price(95)); // Изменили цену
        milk.changeQuantity(-5);  // Уменьшили остаток на 5
        milk.printInfo();

        // Тестируем клонирование (глубокое копирование)
        std::cout << "\n--- Cloning Smartphone ---" << std::endl;
        auto clonedPhone = phone.clone();
        clonedPhone->printInfo(); // У клона будет новый ID (3), но те же данные

        // Тестируем исключение (отрицательная цена)
        std::cout << "\n--- Trying to set negative price ---" << std::endl;
        try {
            Price badPrice(-50);
        }
        catch (const std::exception& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}