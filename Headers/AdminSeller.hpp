#ifndef ADMINSELLER_H
#define ADMINSELLER_H

#include "Seller.hpp"
#include "Manager.hpp"

class AdminSeller : public Seller, public Manager {
public:
    AdminSeller(const std::string& n, double salary);

    std::string getRole() const override;

    void displayInfo() const override;
};

#endif