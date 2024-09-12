#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "product.h"
#include "seller.h"

class Shop {
private:
    std::string name;
    std::vector<std::unique_ptr<Seller> > sellers; 
    std::vector<std::unique_ptr<Product> > products; 

public:
    explicit Shop(const std::string_view n) : name(n) {}

    void addSeller(std::unique_ptr<Seller> seller){
        sellers.push_back(std::move(seller));  
    }

    void removeSeller(const std::string_view sellerName);

    Seller* getSeller(const std::string_view sellerName);

    void addProduct(std::unique_ptr<Product> product) {
        products.push_back(std::move(product)); 
    }

    void removeProduct(const std::string_view productName);

    Product* getProduct(const std::string_view productName);

    void displayShop(bool isAdmin) const;
};

#endif
