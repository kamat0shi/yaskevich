#include "../Headers/Manager.hpp"
#include <iostream>

Manager::Manager(const std::string& n) : name(n) {}

std::string Manager::getRole() const {
    return "Manager";
}

void Manager::displayInfo() const {
    std::cout << "Manager: " << name << std::endl;
}

void Manager::manageShop() const {
    std::cout << "Managing the shop..." << std::endl;
}