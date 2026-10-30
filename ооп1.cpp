#include <iostream>
#include <limits>
#include <string>
#include <memory>
#include <locale>
#define NOMINMAX 
#include <windows.h>
#include "Products.h"
#include "Warehouse.h"
#include "Factories.h"
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    std::cout << "\nНажмите Enter, чтобы продолжить...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        else {
            std::cout << "Ошибка ввода! Введите число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

double getDoubleInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        else {
            std::cout << "Ошибка ввода! Введите число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
std::string getStringInput(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::cin >> value; // Читаем до первого пробела
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер
    return value;
}

void printHeader(const std::string& title) {
    std::cout << "\n============================================\n";
    std::cout << "   " << title << "\n";
    std::cout << "============================================\n";
}


void scenario1() {
    clearScreen();
    printHeader("СЦЕНАРИЙ 1: Создание и добавление");
    Warehouse w(10);

    SmartphoneFactory sf;
    LaptopFactory lf;

    try {
        std::cout << "Добавление смартфона:\n";
        std::string name = getStringInput("Название: ");
        int price = getIntInput("Цена: ");
        int qty = getIntInput("Количество: ");
        double weight = getDoubleInput("Вес (кг): ");
        w.addProduct(sf.createProduct(0, name, price, qty, weight));

        std::cout << "\nДобавление ноутбука:\n";
        name = getStringInput("Название: ");
        price = getIntInput("Цена: ");
        qty = getIntInput("Количество: ");
        weight = getDoubleInput("Вес (кг): ");
        w.addProduct(lf.createProduct(0, name, price, qty, weight));

    }
    catch (const std::exception& e) {
        std::cout << "Ошибка при добавлении: " << e.what() << "\n";
    }

    std::cout << "\n=== Товары на складе ===\n";
    for (const auto& p : w) p->printInfo();
    pauseScreen();
}

void scenario2() {
    clearScreen();
    printHeader("СЦЕНАРИЙ 2: Копирование склада");
    Warehouse original(5);
    SmartphoneFactory sf;

    std::cout << "Создаем товар для оригинала:\n";
    std::string name = getStringInput("Название: ");
    int price = getIntInput("Цена: ");
    int qty = getIntInput("Количество: ");
    double weight = getDoubleInput("Вес (кг): ");
    original.addProduct(sf.createProduct(0, name, price, qty, weight));

    std::cout << "\n--- Оригинал до копирования ---\n";
    for (const auto& p : original) p->printInfo();

    Warehouse copy = original;

    std::cout << "\n--- Изменяем товар В КОПИИ ---\n";
    Product* p = copy.findById(1);
    if (p) {
        int newPrice = getIntInput("Введите новую цену: ");
        int deltaQty = getIntInput("На сколько изменить количество (например, -5): ");
        p->setPrice(Price(newPrice));
        p->changeQuantity(deltaQty);
    }

    std::cout << "\n--- Копия после изменений ---\n";
    for (const auto& item : copy) item->printInfo();

    std::cout << "\n--- Оригинал после изменений копии ---\n";
    for (const auto& item : original) item->printInfo();
    pauseScreen();
}

void scenario3() {
    clearScreen();
    printHeader("СЦЕНАРИЙ 3: Перемещение склада");
    Warehouse w1(5);
    LaptopFactory lf;

    std::cout << "Создаем товар для перемещения:\n";
    std::string name = getStringInput("Название: ");
    int price = getIntInput("Цена: ");
    int qty = getIntInput("Количество: ");
    double weight = getDoubleInput("Вес (кг): ");
    w1.addProduct(lf.createProduct(0, name, price, qty, weight));

    std::cout << "\n--- Склад до перемещения ---\n";
    for (const auto& p : w1) p->printInfo();

    Warehouse w2 = std::move(w1);

    std::cout << "\n--- Новый склад после перемещения ---\n";
    for (const auto& p : w2) p->printInfo();
    std::cout << "Размер: " << w2.size() << "\n";

    std::cout << "\n--- Старый склад после перемещения ---\n";
    std::cout << "Размер: " << w1.size() << " (должен быть 0)\n";
    pauseScreen();
}

void scenario4() {
    clearScreen();
    printHeader("СЦЕНАРИЙ 4: Поиск и удаление");
    Warehouse w(10);
    MilkFactory mf;
    BreadFactory bf;

    w.addProduct(mf.createProduct(0, "Молоко", 80, 20, 1.0));
    w.addProduct(bf.createProduct(0, "Хлеб", 40, 30, 0.5));
    w.addProduct(mf.createProduct(0, "Сыр", 150, 10, 0.3));

    std::cout << "--- Склад ---\n";
    for (const auto& p : w) p->printInfo();

    std::cout << "\n--- Поиск по категории 'food' ---\n";
    auto found = w.findByCategory("food");
    for (auto* p : found) p->printInfo();

    int idToRemove = getIntInput("\nВведите ID товара для удаления: ");
    w.removeById(idToRemove);

    std::cout << "\n--- Склад после удаления ---\n";
    for (const auto& p : w) p->printInfo();
    pauseScreen();
}

void scenario5() {
    clearScreen();
    printHeader("СЦЕНАРИЙ 5: Перемещение товара (transferTo)");
    Warehouse source(5);
    Warehouse dest(5);
    SmartphoneFactory sf;

    std::cout << "Создаем товар на складе-источнике:\n";
    std::string name = getStringInput("Название: ");
    int price = getIntInput("Цена: ");
    int qty = getIntInput("Количество: ");
    double weight = getDoubleInput("Вес (кг): ");
    source.addProduct(sf.createProduct(0, name, price, qty, weight));

    std::cout << "\n--- Склад-источник до переноса ---\n";
    for (const auto& p : source) p->printInfo();

    Product* p = source.findById(1);
    if (p) {
        p->transferTo(dest);
        source.removeById(1);
        std::cout << "Товар перемещен.\n";
    }

    std::cout << "\n--- Склад-получатель после переноса ---\n";
    for (const auto& item : dest) item->printInfo();
    pauseScreen();
}


int main() {
    SetConsoleCP(65001);    
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "Russian");

    while (true) {
        clearScreen();
        std::cout << "   СИСТЕМА УПРАВЛЕНИЯ СКЛАДОМ\n";
        std::cout << " 1. Создание и вывод товаров\n";
        std::cout << " 2. Копирование склада\n";
        std::cout << " 3. Перемещение склада\n";
        std::cout << " 4. Поиск и удаление\n";
        std::cout << " 5. Перемещение товара (transferTo)\n";
        std::cout << " 0. Выход\n";

        int choice = getIntInput("Ваш выбор: ");

        switch (choice) {
        case 1: scenario1(); break;
        case 2: scenario2(); break;
        case 3: scenario3(); break;
        case 4: scenario4(); break;
        case 5: scenario5(); break;
        case 0:
            std::cout << "Выход из программы...\n";
            return 0;
        default:
            std::cout << "Неверный ввод. Попробуйте снова.\n";
            pauseScreen();
        }
    }
    return 0;
}