#include "product.h"
#include <iostream>

using namespace std;

Product::Product(const string& n, double rPrice, double wPrice, int q)
    : name(n), retailPrice(rPrice), wholesalePrice(wPrice), quantity(q) {}

void Product::setName(const string& n) { name = n; }
void Product::setRetailPrice(double rPrice) { retailPrice = rPrice; }
void Product::setWholesalePrice(double wPrice) { wholesalePrice = wPrice; }
void Product::setQuantity(int q) { quantity = q; }

string Product::getName() const { return name; }
double Product::getRetailPrice() const { return retailPrice; }
double Product::getWholesalePrice(bool isAdmin) const {
    if (isAdmin) {
        return wholesalePrice;
    } else {
        cout << "Доступ запрещен: только администратор может просматривать оптовую цену!" << endl;
        return -1;
    }
}
int Product::getQuantity() const { return quantity; }

void Product::displayProduct(bool isAdmin) const {
    cout << "Название: " << name << ", Розничная цена: " << retailPrice << ", Количество: " << quantity << endl;
    if (isAdmin) {
        cout << "Оптовая цена: " << wholesalePrice << endl;
    }
}
