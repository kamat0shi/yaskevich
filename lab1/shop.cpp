#include "shop.h"
#include <iostream>

using namespace std;

Shop::Shop(const string& n) : name(n) {}

void Shop::addSeller(Seller* seller) {
    sellers.push_back(seller);
}

void Shop::removeSeller(const string& sellerName) {
    for (auto it = sellers.begin(); it != sellers.end(); ++it) {
        if ((*it)->getName() == sellerName) {
            delete *it; // Освобождение памяти
            sellers.erase(it);
            cout << "Продавец " << sellerName << " удален." << endl;
            return;
        }
    }
    cout << "Продавец не найден." << endl;
}

Seller* Shop::getSeller(const string& sellerName) {
    for (Seller* seller : sellers) {
        if (seller->getName() == sellerName) {
            return seller;
        }
    }
    return nullptr;
}

void Shop::addProduct(Product* product) {
    products.push_back(product);
}

void Shop::removeProduct(const string& productName) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if ((*it)->getName() == productName) {
            delete *it; // Освобождение памяти
            products.erase(it);
            cout << "Товар " << productName << " удален." << endl;
            return;
        }
    }
    cout << "Товар не найден." << endl;
}

Product* Shop::getProduct(const string& productName) {
    for (Product* product : products) {
        if (product->getName() == productName) {
            return product;
        }
    }
    return nullptr;
}

void Shop::displayShop(bool isAdmin) const {
    cout << "Магазин: " << name << endl;
    cout << "Продавцы:" << endl;
    for (Seller* seller : sellers) {
        seller->displaySeller();
    }
    cout << "Товары:" << endl;
    for (Product* product : products) {
        product->displayProduct(isAdmin);
    }
}

Shop::~Shop() {
    for (Seller* seller : sellers) {
        delete seller; // Освобождение памяти
    }
    for (Product* product : products) {
        delete product; // Освобождение памяти
    }
}
