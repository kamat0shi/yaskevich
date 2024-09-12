#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

class Product{
private:
    std::string name;
    double retailPrice;
    double wholesalePrice;
    int quantity;
public:
    Product(const std::string& n, double rPrice, double wPrice, int q)
        : name(n), retailPrice(rPrice), wholesalePrice(wPrice), quantity(q) {}
    
    void setName(const std::string& n) { name = n; }
    void setRetailPrice(double rPrice) { retailPrice = rPrice; }
    void setWholesalePrice(double wPrice) {wholesalePrice = wPrice; }
    void setQuantity(int q) { quantity = q; }

    std::string getName() const {return name;}
    double getRetailPrice() const {return retailPrice;}
    double getWholesalePrice(bool isAdmin) const {
        if (isAdmin) {
            return wholesalePrice;
        }else{
            std::cout << "Доступ запрещен: только администратор может просматривать оптовую цену!" << std::endl;
            return -1;
        }
    }
    int getQuantity() const { return quantity; } 

    void displayProduct(bool isAdmin) const {
        std::cout << "Название: " << name << ", Розничная цена: " << retailPrice << ", Количество: " << quantity << std::endl;
        if (isAdmin) {
            std::cout << "Оптовая цена: " << wholesalePrice << std::endl;
        }
    }
};

#endif