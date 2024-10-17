#include "../Headers/AdminSeller.hpp"
#include <iostream>

AdminSeller::AdminSeller(const std::string& n, double salary)
    : Seller(n, salary, true), Manager(n) {}

std::string AdminSeller::getRole() const {
    return "Admin Seller (Seller + Manager)";
}

void AdminSeller::displayInfo() const {
    Seller::displayInfo();
    Manager::displayInfo();
}