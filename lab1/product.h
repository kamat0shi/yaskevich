#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

using namespace std;

class Product{
private:
    string name;
    double retailPrice;
    double wholesalePrice;
    int quantity;
public:
    Product(const string& n, double rPrice, double wPrice, int q)
        : name(n), retailPrice(rPrice), wholesalePrice(wPrice), quantity(q) {}
    
    void setName(const string& n) { name = n; }
    void setRetailPrice(double rPrice) { retailPrice = rPrice; }
    void setWholesalePrice(double wPrice) {wholesalePrice = wPrice; }
    void setQuantity(int q) { quantity = q; }

    string getName() const {return name;}
    double getRetailPrice() const {return retailPrice;}
    double getWholesalePrice(bool isAdmin) const {
        if (isAdmin) {
            return wholesalePrice;
        }else{
            cout << "Доступ запрещен: только администратор может просматривать оптовую цену!" << endl;
            return -1;
        }
    }
    int getQuantity() const { return quantity; } 

    void displayProduct(bool isAdmin) const {
        cout << "Название: " << name << ", Розничная цена: " << retailPrice << ", Количество: " << quantity << endl;
        if (isAdmin) {
            cout << "Оптовая цена: " << wholesalePrice << endl;
        }
    }
};

#endif