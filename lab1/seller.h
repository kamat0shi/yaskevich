#ifndef SELLER_H
#define SELLER_H

#include <iostream>
#include <string>

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class Seller{
private:
    std::string name;
    double salary;
    bool isAdmin;

public:
    Seller(const std::string_view n, double s, bool admin = false)
        : name(n), salary(s), isAdmin(admin) {}

    void setName (const std::string_view n) { name = n; }
    void setSalary (double s) { salary = s; }

    std::string getName() const { return name; }
    double getSalary() const { return salary; }
    bool getIsAdmin() const { return isAdmin; }

    void displaySeller() const {
        std::cout << "Имя: " << name << ", Зарплата: " << salary;
        if (isAdmin) {
            std::cout << " (Администратор)";
        }
        std::cout << std::endl;
    }
};

#endif