#include "seller.h"
#include <iostream>

using namespace std;

Seller::Seller(const string& n, double s, bool admin) : name(n), salary(s), isAdmin(admin) {}

void Seller::setName(const string& n) { name = n; }
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
