#ifndef SELLER_H
#define SELLER_H

#include "Person.hpp"
#include <sqlite3.h>

class Seller : public Person {
private:
    std::string name;
    double salary;
    bool isAdmin;

public:
    Seller(const std::string_view n, double s, bool admin = false);

    void setName(const std::string_view n);
    void setSalary(double s);

    std::string getName() const;
    double getSalary() const;
    bool getIsAdmin() const;

    std::string getRole() const override;

    void displayInfo() const override;

    int getIdByName(sqlite3* db, const std::string& sellerName);
};

#endif