#include "shop.h"
#include <iostream>

using namespace std;

void Shop::removeSeller(const std::string_view sellerName) {
    for (auto it = sellers.begin(); it != sellers.end(); ++it) {
        if ((*it)->getName() == sellerName) {
            sellers.erase(it); 
            cout << "Продавец " << sellerName << " удален." << endl;
            return;
        }
    }
    cout << "Продавец не найден." << endl;
}

Seller* Shop::getSeller(const std::string_view sellerName) {
    for (const auto& seller : sellers) {
        if (seller->getName() == sellerName) {
            return seller.get();
        }
    }
    return nullptr;
}

void Shop::removeProduct(const std::string_view productName) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if ((*it)->getName() == productName) {
            products.erase(it);
            cout << "Товар " << productName << " удален." << endl;
            return;
        }
    }
    cout << "Товар не найден." << endl;
}

Product* Shop::getProduct(const std::string_view productName) {
    for (const auto& product : products) {
        if (product->getName() == productName) {
            return product.get();
        }
    }
    return nullptr;
}

void Shop::displayShop(bool isAdmin) const {
    cout << "Магазин: " << name << endl;
    cout << "Продавцы:" << endl;
    for (const auto& seller : sellers) {
        seller->displaySeller();
    }
    cout << "Товары:" << endl;
    for (const auto& product : products) {
        product->displayProduct(isAdmin);
    }
}