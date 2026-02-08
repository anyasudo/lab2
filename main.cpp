#include "car.hpp"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Ru");

    try {
        std::cout << "=== Создание автомобилей с багажниками ===" << std::endl;

        // первый автомобиль
        mt::Car car1("Toyota", "Camry", "А123ВС", { "апельсины", "бананы", "вишня" });
        std::cout << "car1: " << car1 << std::endl;

        // второй автомобиль
        mt::Car car2("BMW", "X5", "М456ОР", { "вишня", "томаты", "клубника" });
        std::cout << "car2: " << car2 << std::endl;

        std::cout << "\n=== Тестирование оператора + (объединение с повторами) ===" << std::endl;
        mt::Car car3 = car1 + car2;
        std::cout << "car1 + car2 = " << car3 << std::endl;
        std::cout << "Ожидается: [Toyota,<случайный номер>,(апельсины,бананы,вишня,вишня,томаты,клубника)]" << std::endl;

        std::cout << "\n=== Тестирование оператора - (уникальные вещи) ===" << std::endl;
        mt::Car car4 = car1 - car2;
        std::cout << "car1 - car2 = " << car4 << std::endl;
        std::cout << "Ожидается: [Toyota,<случайный номер>,(апельсины,бананы,вишня,томаты,клубника)]" << std::endl;

        std::cout << "\n=== Тестирование оператора / (общие вещи) ===" << std::endl;
        mt::Car car5 = car1 / car2;
        std::cout << "car1 / car2 = " << car5 << std::endl;
        std::cout << "Ожидается: [BMW,<случайный номер>,(вишня)]" << std::endl;

        std::cout << "\n=== Еще примеры ===" << std::endl;

        // автомобили с одинаковыми предметами
        mt::Car car6("Lada", "Granta", "О789РТ", { "яблоки", "груши", "яблоки" });
        mt::Car car7("Kia", "Rio", "Х123СТ", { "груши", "сливы", "яблоки" });

        std::cout << "car6: " << car6 << std::endl;
        std::cout << "car7: " << car7 << std::endl;

        std::cout << "\ncar6 + car7 = " << (car6 + car7) << std::endl;
        std::cout << "car6 - car7 = " << (car6 - car7) << std::endl;
        std::cout << "car6 / car7 = " << (car6 / car7) << std::endl;

        std::cout << "\n=== Тестирование других методов ===" << std::endl;
        car1.add_to_trunk("мандарины");
        std::cout << "car1 после добавления: " << car1 << std::endl;

        car1.remove_from_trunk("бананы");
        std::cout << "car1 после удаления: " << car1 << std::endl;

        std::cout << "\n=== Проверка геттеров ===" << std::endl;
        std::cout << "Марка car1: " << car1.get_brand() << std::endl;
        std::cout << "Вещи в багажнике car1: ";
        for (const auto& item : car1.get_trunk_items()) {
            std::cout << item << " ";
        }
        std::cout << std::endl;

        std::cout << "\n=== Проверка сеттера госномера ===" << std::endl;
        try {
            car1.set_license_plate("Е555КХ");
            std::cout << "car1 после смены номера: " << car1 << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }

        std::cout << "\n=== Проверка с неправильным номером ===" << std::endl;
        try {
            car1.set_license_plate("Я123ВС");  // Я не разрешена
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }

    std::cout << "\n=== Конец программы ===" << std::endl;
    return 0;
}
