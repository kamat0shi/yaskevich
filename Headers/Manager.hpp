#ifndef MANAGER_H
#define MANAGER_H

#include "Person.hpp"

class Manager : public Person {
private:
    std::string name;

public:
    Manager(const std::string& n);

    // Реализация чистой виртуальной функции getRole
    std::string getRole() const override;

    // Переопределение функции displayInfo
    void displayInfo() const override;

    void manageShop() const;
};

#endif