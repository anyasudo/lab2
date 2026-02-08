#ifndef CAR_HPP
#define CAR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

namespace mt {

    class Car {
    private:
        std::string brand_;
        std::string model_;
        std::string body_number_;
        std::string license_plate_;
        int mileage_;

        // динамическое поле для истории пробегов
        std::vector<int>* mileage_history_;

        bool is_mileage_valid_(int mileage) const {
            return mileage >= 0;
        }

        // проверка гос номера 
        bool check_license_format_(const std::string& plate) const;

    protected:
        void show_protected_info_() const {
            std::cout << "[Protected доступ] Марка авто: " << brand_ << std::endl;
        }

        std::string car_color_ = "Не указан";

    public:
        // конструктор по умолчанию
        Car();

        // конструктор полного заполнения
        Car(const std::string& brand, const std::string& model,
            const std::string& body_number, const std::string& license_plate,
            int mileage);

        // конструктор копирования 
        Car(const Car& other);

        // оператор присваивания 
        Car& operator=(const Car& other);

        // деструктор 
        ~Car();

        // геттеры на все поля
        std::string get_brand() const { return brand_; }
        std::string get_model() const { return model_; }
        std::string get_body_number() const { return body_number_; }
        std::string get_license_plate() const { return license_plate_; }
        int get_mileage() const { return mileage_; }
        const std::vector<int>* get_mileage_history() const { return mileage_history_; }

        // сеттер для номера кузова 
        void set_body_number(const std::string& body_number);

        // сеттер для гос. номера с проверкой 
        void set_license_plate(const std::string& license_plate);

        // метод для вывода всей информации 
        void print_info() const;

        // метод для скручивания пробега на X 
        void rollback_mileage(int x);

        // метод для увеличения пробега 
        void drive(int distance);

        // оператор сравнения == по гос номеру
        bool operator==(const Car& other) const;

        // оператор сравнения !=
        bool operator!=(const Car& other) const;

        // оператор вывода в поток
        friend std::ostream& operator<<(std::ostream& os, const Car& car);

        // публичные методы для работы с protected данными
        void set_color(const std::string& color);
        void show_color() const;

        // метод для отображения истории пробегов
        void show_mileage_history() const;
    };

} 

#endif // CAR_HPP