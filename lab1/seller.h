#ifndef SELLER_H
#define SELLER_H

#include <iostream>
#include <string>

using namespace std;

class Seller{
protected:
    string name;
    double salary;
    bool isAdmin;

public:
    Seller(const string& n, double s, bool admin = false)
        : name(n), salary(s), isAdmin(admin) {}

    void setName (const string& n) { name = n; }
    void setSalary (double s) { salary = s; }

    string getName() const { return name; }
    double getSalary() const { return salary; }
    bool getIsAdmin() const { return isAdmin; }

    void displaySeller() const {
        cout << "Имя: " << name << ", Зарплата: " << salary;
        if (isAdmin) {
            cout << " (Администратор)";
        }
        cout << endl;
    }
};

#endif