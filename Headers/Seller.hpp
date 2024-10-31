#ifndef SELLER_H
#define SELLER_H

#include "Person.hpp"
#include "../Headers/Sale.hpp" 
#include <sqlite3.h>
#include <string>
#include <sstream>

class Seller : public Person {
private:
    std::string name;
    double salary;
    bool isAdmin;

    friend std::ostream& operator<<(std::ostream& os, const Seller& seller) {
    os << "Продавец: " << seller.name 
       << ", Зарплата: " << seller.salary 
       << ", Админ: " << (seller.isAdmin ? "Да" : "Нет");
    return os;
}
public:
    Seller(const std::string_view n, double s, bool admin = false);

    void setName(const std::string_view n);
    void setSalary(double s);

    std::string getName() const;
    double getSalary() const;
    bool getIsAdmin() const;

    std::string getRole() const override;

    void displayInfo() const override;
    std::string getInfo() const;

    int getIdByName(sqlite3* db, const std::string& sellerName) const;

};

#endif