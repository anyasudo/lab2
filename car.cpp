#include "car.hpp"

namespace mt {

    // проверка гос номера 
    bool Car::check_license_format_(const std::string& plate) const {
        if (plate.length() != 6) {
            return false;
        }

        std::string allowed_letters = "АВЕКМНОРСТУХ";

        // первый символ должен быть буква из списка
        bool first_ok = false;
        for (char letter : allowed_letters) {
            if (plate[0] == letter) {
                first_ok = true;
                break;
            }
        }

        // 2-4 символы должны быть цифры
        bool digits_ok = true;
        for (int i = 1; i <= 3; i++) {
            if (plate[i] < '0' || plate[i] > '9') {
                digits_ok = false;
                break;
            }
        }

        // 5-6 символы должны быть буквы из списка
        bool last_ok = false;
        for (char letter1 : allowed_letters) {
            for (char letter2 : allowed_letters) {
                if (plate[4] == letter1 && plate[5] == letter2) {
                    last_ok = true;
                    break;
                }
            }
            if (last_ok) break;
        }

        return first_ok && digits_ok && last_ok;
    }

    // конструктор по умолчанию
    Car::Car() : brand_("Неизвестно"), model_("Неизвестно"),
        body_number_("000000"), license_plate_("А000АА"),
        mileage_(0) {

        mileage_history_ = new std::vector<int>();
        mileage_history_->push_back(0); // начальный пробег
        std::cerr << "Вызван конструктор по умолчанию" << std::endl;
    }

    // конструктор полного заполнения
    Car::Car(const std::string& brand, const std::string& model,
        const std::string& body_number, const std::string& license_plate,
        int mileage) :
        brand_(brand), model_(model), body_number_(body_number),
        license_plate_(license_plate), mileage_(mileage) {

        if (!is_mileage_valid_(mileage)) {
            throw std::invalid_argument("Пробег должен быть неотрицательным");
        }

        // проверка гос номера
        if (!check_license_format_(license_plate)) {
            throw std::invalid_argument(
                "Гос. номер должен быть в формате: БУКВА + 3 ЦИФРЫ + 2 БУКВЫ\n"
                "Разрешенные буквы: А, В, Е, К, М, Н, О, Р, С, Т, У, Х\n"
                "Пример: А123ВС, М456ОР, Х789ТУ");
        }

        mileage_history_ = new std::vector<int>();
        mileage_history_->push_back(mileage); // начальный пробег

        std::cerr << "Вызван конструктор с параметрами" << std::endl;
        show_protected_info_();
    }

    // конструктор копирования
    Car::Car(const Car& other) :
        brand_(other.brand_), model_(other.model_),
        body_number_(other.body_number_),
        license_plate_(other.license_plate_),
        mileage_(other.mileage_) {

        // глубокое копирование динамического поля
        mileage_history_ = new std::vector<int>(*other.mileage_history_);

        std::cerr << "Вызван конструктор копирования" << std::endl;
    }

    // оператор присваивания
    Car& Car::operator=(const Car& other) {
        std::cerr << "Вызван оператор присваивания" << std::endl;

        if (this != &other) { // защита от самоприсваивания
            brand_ = other.brand_;
            model_ = other.model_;
            body_number_ = other.body_number_;
            license_plate_ = other.license_plate_;
            mileage_ = other.mileage_;

            delete mileage_history_;

            mileage_history_ = new std::vector<int>(*other.mileage_history_);
        }

        return *this;
    }

    // деструктор
    Car::~Car() {
        // Очистка динамического поля перед выводом сообщения
        if (mileage_history_ != nullptr) {
            mileage_history_->clear(); // очистка вектора
            delete mileage_history_;   // освобождение памяти
            mileage_history_ = nullptr;
        }

        std::cerr << "Вызван деструктор для " << brand_ << " " << model_ << std::endl;
    }

    // сеттер для номера кузова
    void Car::set_body_number(const std::string& body_number) {
        body_number_ = body_number;
    }

    // сеттер для гос. номера с проверкой 
    void Car::set_license_plate(const std::string& license_plate) {
        if (!check_license_format_(license_plate)) {
            throw std::invalid_argument(
                "Гос. номер должен быть в формате: БУКВА + 3 ЦИФРЫ + 2 БУКВЫ\n"
                "Разрешенные буквы: А, В, Е, К, М, Н, О, Р, С, Т, У, Х\n"
                "Пример: А123ВС, М456ОР, Х789ТУ");
        }

        license_plate_ = license_plate;
        std::cout << "Гос. номер успешно изменен на: " << license_plate_ << std::endl;
    }

    // метод для вывода всей информации
    void Car::print_info() const {
        std::cout << "=== Информация об автомобиле ===" << std::endl;
        std::cout << "Марка: " << brand_ << std::endl;
        std::cout << "Модель: " << model_ << std::endl;
        std::cout << "Номер кузова: " << body_number_ << std::endl;
        std::cout << "Гос. номер: " << license_plate_ << std::endl;
        std::cout << "Пробег: " << mileage_ << " км" << std::endl;
        std::cout << "================================" << std::endl;
    }

    // метод для скручивания пробега на X
    void Car::rollback_mileage(int x) {
        if (x < 0) {
            throw std::invalid_argument("Значение скручивания должно быть неотрицательным");
        }

        if (mileage_ - x < 0) {
            throw std::invalid_argument("Нельзя скрутить больше, чем текущий пробег");
        }

        mileage_ -= x;
        mileage_history_->push_back(mileage_); // в историю
        std::cout << "Пробег уменьшен на " << x << " км" << std::endl;
    }

    // метод для увеличения пробега
    void Car::drive(int distance) {
        if (distance < 0) {
            throw std::invalid_argument("Расстояние должно быть неотрицательным");
        }
        mileage_ += distance;
        mileage_history_->push_back(mileage_); // в историю
        std::cout << "Автомобиль проехал " << distance << " км" << std::endl;
    }

    // оператор сравнения == по гос номеру
    bool Car::operator==(const Car& other) const {
        return license_plate_ == other.license_plate_;
    }

    // оператор сравнения !=
    bool Car::operator!=(const Car& other) const {
        return !(*this == other);
    }

    // оператор вывода в поток
    std::ostream& operator<<(std::ostream& os, const Car& car) {
        os << car.brand_ << " " << car.model_ << " (" << car.license_plate_ << ") - "
            << car.mileage_ << " км";
        return os;
    }

    // публичные методы для работы с protected данными
    void Car::set_color(const std::string& color) {
        car_color_ = color;
        std::cout << "Цвет автомобиля установлен: " << car_color_ << std::endl;
    }

    void Car::show_color() const {
        std::cout << "Цвет автомобиля: " << car_color_ << std::endl;
    }

    // метод для отображения истории пробегов
    void Car::show_mileage_history() const {
        std::cout << "=== История пробегов ===" << std::endl;
        if (mileage_history_ == nullptr || mileage_history_->empty()) {
            std::cout << "История пуста" << std::endl;
        }
        else {
            for (size_t i = 0; i < mileage_history_->size(); ++i) {
                std::cout << "Запись " << (i + 1) << ": " << (*mileage_history_)[i] << " км" << std::endl;
            }
        }
        std::cout << "========================" << std::endl;
    }

} 