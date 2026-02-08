#include "car.hpp"
#include <algorithm>
#include <random>
#include <chrono>

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

    // генерация случайного госномера
    std::string Car::generate_random_plate_() const {
        static const std::string letters = "АВЕКМНОРСТУХ";
        static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        static std::uniform_int_distribution<int> letter_dist(0, letters.size() - 1);
        static std::uniform_int_distribution<int> digit_dist(0, 9);

        std::string plate;

        // до тех пор пока не получим валидный
        do {
            plate.clear();
            plate += letters[letter_dist(rng)];  // первая буква
            plate += std::to_string(digit_dist(rng));  // первая цифра
            plate += std::to_string(digit_dist(rng));  // вторая цифра
            plate += std::to_string(digit_dist(rng));  // третья цифра
            plate += letters[letter_dist(rng)];  // четвертая буква
            plate += letters[letter_dist(rng)];  // пятая буква
        } while (!check_license_format_(plate));

        return plate;
    }

    // конструктор по умолчанию
    Car::Car() : brand_("Неизвестно"), model_("Неизвестно"),
        license_plate_("А000АА") {
        std::cerr << "Вызван конструктор по умолчанию" << std::endl;
    }

    // конструктор полного заполнения
    Car::Car(const std::string& brand, const std::string& model,
        const std::string& license_plate,
        const std::vector<std::string>& trunk_items) :
        brand_(brand), model_(model), license_plate_(license_plate),
        trunk_items_(trunk_items) {

        // проверка гос. номера
        if (!check_license_format_(license_plate)) {
            throw std::invalid_argument(
                "Гос. номер должен быть в формате: БУКВА + 3 ЦИФРЫ + 2 БУКВЫ\n"
                "Разрешенные буквы: А, В, Е, К, М, Н, О, Р, С, Т, У, Х\n"
                "Пример: А123ВС, М456ОР, Х789ТУ");
        }

        std::cerr << "Вызван конструктор с параметрами" << std::endl;
    }

    // конструктор копирования
    Car::Car(const Car& other) :
        brand_(other.brand_), model_(other.model_),
        license_plate_(other.license_plate_),
        trunk_items_(other.trunk_items_) {

        std::cerr << "Вызван конструктор копирования" << std::endl;
    }

    // оператор присваивания
    Car& Car::operator=(const Car& other) {
        std::cerr << "Вызван оператор присваивания" << std::endl;

        if (this != &other) {
            brand_ = other.brand_;
            model_ = other.model_;
            license_plate_ = other.license_plate_;
            trunk_items_ = other.trunk_items_;
        }

        return *this;
    }

    // деструктор
    Car::~Car() {
        std::cerr << "Вызван деструктор для " << brand_ << " " << model_ << std::endl;
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
        std::cout << "Гос. номер: " << license_plate_ << std::endl;
        std::cout << "Вещи в багажнике (" << trunk_items_.size() << "): ";

        if (trunk_items_.empty()) {
            std::cout << "багажник пуст";
        }
        else {
            for (size_t i = 0; i < trunk_items_.size(); ++i) {
                std::cout << trunk_items_[i];
                if (i < trunk_items_.size() - 1) {
                    std::cout << ", ";
                }
            }
        }
        std::cout << std::endl << "================================" << std::endl;
    }

    // метод для добавления вещей в багажник
    void Car::add_to_trunk(const std::string& item) {
        trunk_items_.push_back(item);
        std::cout << "Добавлено в багажник: " << item << std::endl;
    }

    // метод для удаления вещей из багажника
    void Car::remove_from_trunk(const std::string& item) {
        auto it = std::find(trunk_items_.begin(), trunk_items_.end(), item);
        if (it != trunk_items_.end()) {
            trunk_items_.erase(it);
            std::cout << "Удалено из багажника: " << item << std::endl;
        }
        else {
            std::cout << "Предмет " << item << " не найден в багажнике" << std::endl;
        }
    }

    // оператор + 
    Car Car::operator+(const Car& other) const {
        std::cout << "Выполняется оператор +" << std::endl;

        Car result;

        result.brand_ = this->brand_;
        result.model_ = this->model_;

        result.license_plate_ = generate_random_plate_();

        result.trunk_items_ = this->trunk_items_;
        result.trunk_items_.insert(result.trunk_items_.end(),
            other.trunk_items_.begin(),
            other.trunk_items_.end());

        return result;
    }

    // оператор - 
    Car Car::operator-(const Car& other) const {
        std::cout << "Выполняется оператор -" << std::endl;

        Car result;

        result.brand_ = this->brand_;
        result.model_ = this->model_;

        result.license_plate_ = generate_random_plate_();

        std::vector<std::string> all_items = this->trunk_items_;
        all_items.insert(all_items.end(), other.trunk_items_.begin(), other.trunk_items_.end());

        std::sort(all_items.begin(), all_items.end());
        auto last = std::unique(all_items.begin(), all_items.end());
        all_items.erase(last, all_items.end());

        result.trunk_items_ = all_items;

        return result;
    }

    // оператор / 
    Car Car::operator/(const Car& other) const {
        std::cout << "Выполняется оператор /" << std::endl;

        Car result;

        result.brand_ = other.brand_;
        result.model_ = other.model_;

        result.license_plate_ = generate_random_plate_();

        for (const auto& item1 : this->trunk_items_) {
            for (const auto& item2 : other.trunk_items_) {
                if (item1 == item2) {
                    if (std::find(result.trunk_items_.begin(), result.trunk_items_.end(), item1)
                        == result.trunk_items_.end()) {
                        result.trunk_items_.push_back(item1);
                    }
                    break;
                }
            }
        }

        return result;
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
        os << "[" << car.brand_ << "," << car.license_plate_ << ",(";

        if (car.trunk_items_.empty()) {
            os << "пусто";
        }
        else {
            for (size_t i = 0; i < car.trunk_items_.size(); ++i) {
                os << car.trunk_items_[i];
                if (i < car.trunk_items_.size() - 1) {
                    os << ",";
                }
            }
        }

        os << ")]";
        return os;
    }

} 
