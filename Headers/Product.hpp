#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

class Product {
private:
    std::string name;
    double retailPrice;
    double wholesalePrice;
    int quantity;

    // Скрытые друзья
    friend bool compareQuantity(const Product& p1, const Product& p2);

    // Скрытый друг для оператора сложения (объявлен и определён в классе)
    friend Product operator+(Product lhs, int additionalQty) {
        lhs.quantity += additionalQty;
        return lhs;
    }

    // Скрытый друг для оператора вывода (объявлен и определён в классе)
    friend std::ostream& operator<<(std::ostream& os, const Product& product) {
        os << "Название: " << product.name
           << ", Розничная цена: " << product.retailPrice
           << ", Количество: " << product.quantity;
        return os;
    }

public:
    Product(const std::string_view n, double rPrice, double wPrice, int q);

    void setName(const std::string_view n);
    void setRetailPrice(double rPrice);
    void setWholesalePrice(double wPrice);
    void setQuantity(int q);

    std::string getName() const;
    double getRetailPrice() const;
    double getWholesalePrice(bool isAdmin) const;
    int getQuantity() const;

    void reduceQuantity(int qty);

    void displayProduct(bool isAdmin) const;
};

#endif