#ifndef SHOP_H
#define SHOP_H

#include "../Headers/Container.hpp"
#include "../Headers/Seller.hpp"
#include "../Headers/Product.hpp"
#include "../Headers/Sale.hpp" 
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <vector>

class Shop {
private:
    std::string name;
    int shop_id;
    sqlite3* db;

    Container<Seller> sellers;   
    Container<Product> products;

    void fetchShopIdByName();
    void loadSellersFromDB();
    void loadProductsFromDB();

public:
    Shop(const std::string_view n, sqlite3* db);

    void addSeller(std::unique_ptr<Seller> seller);
    void removeSeller(const std::string_view sellerName);
    Seller* getSeller(const std::string_view sellerName);

    void addProduct(std::unique_ptr<Product> product);
    void removeProduct(const std::string_view productName);
    Product* getProduct(const std::string_view productName);

    void makeSale(const std::string_view productName, int qty, double discount, const std::string& sellerName);

    void displayShop(bool isAdmin = false) const;
    void displaySalesHistory() const;

    const std::vector<std::unique_ptr<Seller>>& getSellers() const;
    const std::vector<std::unique_ptr<Product>>& getProducts() const;
    std::vector<Sale> getSalesHistory() const;
};

#endif