#ifndef SHOP_H
#define SHOP_H

#include "Product.hpp"
#include "Seller.hpp"
#include "Sale.hpp"
#include <vector>
#include <memory>
#include <ranges>
#include <sqlite3.h>

class Shop {
private:
    std::string name;
    std::vector<std::unique_ptr<Seller>> sellers;
    std::vector<std::unique_ptr<Product>> products;
    std::vector<Sale> salesHistory;
    sqlite3* db;  

public:
    explicit Shop(const std::string_view n, sqlite3* db);

    void addSeller(std::unique_ptr<Seller> seller);
    void removeSeller(const std::string_view sellerName);
    Seller* getSeller(const std::string_view sellerName);

    void addProduct(std::unique_ptr<Product> product);
    void removeProduct(const std::string_view productName);
    Product* getProduct(const std::string_view productName);

    void displayShop(bool isAdmin) const;

    void makeSale(const std::string_view productName, int qty, double discount = 0);

    void displaySalesHistory() const;
};

#endif