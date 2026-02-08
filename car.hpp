#ifndef CAR_HPP
#define CAR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <random>

namespace mt {

    class Car {
    private:
        std::string brand_;
        std::string model_;
        std::string license_plate_;
        std::vector<std::string> trunk_items_;  // вещи в багажнике

        // проверка гос номера
        bool check_license_format_(const std::string& plate) const;

        // генерация случайного госномера
        std::string generate_random_plate_() const;

    public:
        // конструктор по умолчанию
        Car();

        // конструктор полного заполнения
        Car(const std::string& brand, const std::string& model,
            const std::string& license_plate,
            const std::vector<std::string>& trunk_items = {});

        // конструктор копирования
        Car(const Car& other);

        // оператор присваивания
        Car& operator=(const Car& other);

        // деструктор
        ~Car();

        // геттеры
        std::string get_brand() const { return brand_; }
        std::string get_model() const { return model_; }
        std::string get_license_plate() const { return license_plate_; }
        std::vector<std::string> get_trunk_items() const { return trunk_items_; }

        // сеттер для гос. номера с проверкой
        void set_license_plate(const std::string& license_plate);

        // метод для вывода всей информации
        void print_info() const;

        // метод для добавления вещей в багажник
        void add_to_trunk(const std::string& item);

        // метод для удаления вещей из багажника
        void remove_from_trunk(const std::string& item);

        // оператор + 
        Car operator+(const Car& other) const;

        // оператор - 
        Car operator-(const Car& other) const;

        // оператор / 
        Car operator/(const Car& other) const;

        // оператор сравнения ==
        bool operator==(const Car& other) const;

        // оператор сравнения !=
        bool operator!=(const Car& other) const;

        // оператор вывода в поток
        friend std::ostream& operator<<(std::ostream& os, const Car& car);
    };

}

#endif // CAR_HPP
