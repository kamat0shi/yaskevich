#ifndef ADMINSELLER_H
#define ADMINSELLER_H

#include "Seller.hpp"
#include "Manager.hpp"

class AdminSeller : public Seller, public Manager {
public:
    AdminSeller(const std::string& n, double salary);

    // Переопределение виртуальной функции
    std::string getRole() const override;

    // Переопределение функции для вывода информации
    void displayInfo() const override;
};

#endif