#include "seller.h"
#include <iostream>
#include <memory>

using namespace std;

void Seller::setName(const std::string_view n) { name = n; }
void Seller::setSalary(double s) { salary = s; }

string Seller::getName() const { return name; }
double Seller::getSalary() const { return salary; }
bool Seller::getIsAdmin() const { return isAdmin; }

void Seller::displaySeller() const {
    cout << "Имя: " << name << ", Зарплата: " << salary;
    if (isAdmin) {
        cout << " (Администратор)";
    }
    cout << endl;
}
