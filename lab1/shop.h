#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include <string>
#include "product.h"
#include "seller.h"

using namespace std;

class Shop {
private:
    string name;
    vector<Seller*> sellers;
    vector<Product*> products;
public:
    Shop(const string& n) : name(n) {}

    void addSeller(Seller* seller){
        sellers.push_back(seller);
    }
    
    void removeSeller(const string& sellerName){
        for (auto it = sellers.begin(); it != sellers.end(); ++it){
            if ((*it)->getName() == sellerName){
                delete *it;
                sellers.erase(it);
                cout << "Продавец " << sellerName << " удален." << endl;
                return;
            }
        }
        cout << "Продавец не найден." << endl;
    }

    Seller* getSeller(const string& sellerName) {
        for (Seller* seller : sellers){
            if (seller->getName() == sellerName){
                return seller;
            }
        }
        return nullptr;
    }

    void addProduct(Product* product) {
        products.push_back(product);
    }

    void removeProduct(const string& productName) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if ((*it)->getName() == productName) {
                delete *it;
                products.erase(it);
                cout << "Товар " << productName << " удален." << endl;
                return;
            }
        }
        cout << "Товар не найден." << endl;
    }

    Product* getProduct(const string& productName) {
        for (Product* product : products) {
            if (product->getName() == productName) {
                return product;
            }
        }
        return nullptr;
    }

    void displayShop(bool isAdmin) const {
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

    ~Shop() {
        for (Seller* seller : sellers) {
            delete seller; // Освобождение памяти
        }
        for (Product* product : products) {
            delete product; // Освобождение памяти
        }
    }
};

#endif