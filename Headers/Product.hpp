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

    friend bool compareQuantity(const Product& p1, const Product& p2);
    friend std::ostream& operator<<(std::ostream& os, const Product& product);
    
public:
    bool operator==(const Product& other) const;
    Product& operator+(int additionalQty);

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
