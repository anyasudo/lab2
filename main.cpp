#include "car.hpp"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Ru");

    try {
        std::cout << "=== ТЕСТИРОВАНИЕ ДИНАМИЧЕСКОГО ПОЛЯ ===" << std::endl;

        // Создаем автомобили
        mt::Car car1("Toyota", "Camry", "А123ВС", { "яблоки", "бананы", "яблоки", "вишня" });
        mt::Car car2("BMW", "X5", "М456ОР", { "вишня", "томаты", "вишня", "клубника" });

        std::cout << "car1: " << car1 << std::endl;
        std::cout << "car2: " << car2 << std::endl;

        std::cout << "\n=== ТЕСТИРОВАНИЕ ОПЕРАТОРА (повторы рядом) ===" << std::endl;
        mt::Car car3 = car1 + car2;
        std::cout << "car1 + car2 = " << car3 << std::endl;
        std::cout << "Ожидается: повторы должны быть сгруппированы рядом" << std::endl;

        std::cout << "\n=== ТЕСТИРОВАНИЕ ПРАВИЛА ТРЕХ ===" << std::endl;

        // Тест конструктора копирования
        std::cout << "\n--- Конструктор копирования ---" << std::endl;
        mt::Car car4 = car1;
        std::cout << "car4 (копия car1): " << car4 << std::endl;

        // Тест оператора присваивания
        std::cout << "\n--- Оператор присваивания ---" << std::endl;
        mt::Car car5;
        car5 = car2;
        std::cout << "car5 (после присваивания car2): " << car5 << std::endl;

        // Тест что копии независимы
        std::cout << "\n--- Проверка независимости копий ---" << std::endl;
        car1.add_to_trunk("мандарины");
        std::cout << "car1 после добавления: " << car1 << std::endl;
        std::cout << "car4 (копия car1) должна остаться без изменений: " << car4 << std::endl;

        // Тест деструктора
        std::cout << "\n--- Скоро вызовутся деструкторы (смотрим вывод) ---" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }

    std::cout << "\n=== КОНЕЦ ПРОГРАММЫ (здесь будут вызываться деструкторы) ===" << std::endl;
    return 0;
}
