#include "../Headers/Seller.hpp"

Seller::Seller(const std::string_view n, double s, bool admin) : name(n), salary(s), isAdmin(admin) {}

void Seller::setName(const std::string_view n) { name = n; }
void Seller::setSalary(double s) { salary = s; }

std::string Seller::getName() const { return name; }
double Seller::getSalary() const { return salary; }
bool Seller::getIsAdmin() const { return isAdmin; }

void Seller::displaySeller() const {
    std::cout << "Имя: " << name << ", Зарплата: " << salary;
    if (isAdmin) {
        std::cout << " (Администратор)";
    }
    std::cout << std::endl;
}
