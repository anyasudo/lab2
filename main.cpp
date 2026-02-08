#include "car.hpp"

int main() {
    setlocale(LC_ALL, "Ru");

    try {
        std::cout << "=== Создание car1 с конструктором по умолчанию ===" << std::endl;
        mt::Car car1;
        car1.print_info();

        // работа с protected данными через публичные методы
        car1.show_color();
        car1.set_color("Красный");
        car1.show_color();

        std::cout << "\n=== Создание car2 с конструктором с параметрами ===" << std::endl;
        mt::Car car2("Toyota", "Camry", "123456789", "А123ВС", 50000);
        car2.print_info();

        // история пробегов
        car2.show_mileage_history();

        std::cout << "\n=== Создание car3 как копии car2 ===" << std::endl;
        mt::Car car3 = car2;
        car3.print_info();

        std::cout << "\n=== Тестирование оператора присваивания ===" << std::endl;
        mt::Car car4;
        car4 = car2; // оператор присваивания
        std::cout << "car4 после присваивания: " << car4 << std::endl;

        std::cout << "\n=== Тестирование сеттеров на car1 ===" << std::endl;
        car1.set_body_number("987654321");

        // тестирование сеттера с правильным номером
        car1.set_license_plate("М456ОР");
        car1.print_info();

        // тестирование с неправильным номером
        std::cout << "\n=== Тестирование с неправильным номером ===" << std::endl;
        try {
            car1.set_license_plate("АБВ123");
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }

        std::cout << "\n=== Тестирование метода поездки ===" << std::endl;
        car1.drive(100);
        car1.drive(50);
        car1.print_info();
        car1.show_mileage_history();

        std::cout << "\n=== Тестирование скручивания пробега ===" << std::endl;
        car1.rollback_mileage(50);
        car1.print_info();
        car1.show_mileage_history();

        std::cout << "\n=== Тестирование геттеров ===" << std::endl;
        std::cout << "Марка: " << car2.get_brand() << std::endl;
        std::cout << "Модель: " << car2.get_model() << std::endl;
        std::cout << "Пробег: " << car2.get_mileage() << " км" << std::endl;

        // Тестирование операторов сравнения
        std::cout << "\n=== Тестирование операторов сравнения ===" << std::endl;
        std::cout << "car1 == car2: " << (car1 == car2) << std::endl;
        std::cout << "car1 != car2: " << (car1 != car2) << std::endl;
        std::cout << "car2 == car3: " << (car2 == car3) << std::endl;

        // Тестирование оператора вывода
        std::cout << "\n=== Тестирование оператора вывода << ===" << std::endl;
        std::cout << "car1: " << car1 << std::endl;
        std::cout << "car2: " << car2 << std::endl;
        std::cout << "car3: " << car3 << std::endl;

        // тест на ошибки с пробегом
        std::cout << "\n=== Тестирование обработки ошибок ===" << std::endl;
        try {
            car1.rollback_mileage(1000); // больше чем пробег
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }

        // тесты с созданием авто с ошибками
        std::cout << "\n=== Тесты создания авто с ошибками ===" << std::endl;
        try {
            std::cout << "\nПопытка создать машину с отрицательным пробегом:" << std::endl;
            mt::Car error_car("BMW", "X5", "555555", "Х555ХХ", -100);
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка при создании: " << e.what() << std::endl;
        }

        try {
            std::cout << "\nПопытка создать машину с неправильным номером:" << std::endl;
            mt::Car error_car2("BMW", "X5", "555555", "ПРИВЕТ", 10000);
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка при создании: " << e.what() << std::endl;
        }

        std::cout << "\n=== Примеры правильных номеров ===" << std::endl;
        std::cout << "Правильные номера: А123ВС, Е456КМ, О789РТ, Х123СТ" << std::endl;
        std::cout << "Неправильные: Я123ВС (Я не разрешена), АБВ123 (буквы не там), 123АВС (начинается с цифры)" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }

    std::cout << "\n=== Конец программы ===" << std::endl;
    return 0;
}