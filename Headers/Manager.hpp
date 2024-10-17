#ifndef MANAGER_H
#define MANAGER_H

#include "Person.hpp"

class Manager : public Person {
private:
    std::string name;

public:
    explicit Manager(const std::string& n);

    std::string getRole() const override;

    void displayInfo() const override;

    void manageShop() const;
};

#endif