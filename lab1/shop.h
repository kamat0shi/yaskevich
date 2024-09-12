#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include <string>
#include "product.h"
#include "seller.h"

class Shop {
private:
    std::string name;
    vector<Seller*> sellers;
    vector<Product*> products;
public:
    Shop(const std::string_view n) : name(n) {}

    void addSeller(Seller* seller){
        sellers.push_back(seller);
    }
    
    void removeSeller(const std::string_view sellerName){
        for (auto it = sellers.begin(); it != sellers.end(); ++it){
            if ((*it)->getName() == sellerName){
                delete *it;
                sellers.erase(it);
                std::cout << "Продавец " << sellerName << " удален." << std::endl;
                return;
            }
        }
        std::cout << "Продавец не найден." << std::endl;
    }

    Seller* getSeller(const std::string_view sellerName) {
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

    void removeProduct(const std::string_view productName) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if ((*it)->getName() == productName) {
                delete *it;
                products.erase(it);
                std::cout << "Товар " << productName << " удален." << std::endl;
                return;
            }
        }
        std::cout << "Товар не найден." << std::endl;
    }

    Product* getProduct(const std::string_view productName) {
        for (Product* product : products) {
            if (product->getName() == productName) {
                return product;
            }
        }
        return nullptr;
    }

    void displayShop(bool isAdmin) const {
        std::cout << "Магазин: " << name << std::endl;
        std::cout << "Продавцы:" << std::endl;
        for (Seller* seller : sellers) {
            seller->displaySeller();
        }
        std::cout << "Товары:" << std::endl;
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