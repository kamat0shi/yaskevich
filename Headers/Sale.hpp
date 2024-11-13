#ifndef SALE_HPP
#define SALE_HPP

#include <string>
#include <iostream>

class Sale {
private:
    std::string productName;
    int quantitySold;
    double salePrice;
    double discountApplied;
    double profit;
    std::string sellerName;

public:
    Sale(const std::string& productName, int qty, double salePrice, double discount, double profit, const std::string& sellerName);

    std::string getProductName() const;
    int getQuantitySold() const;
    double getSalePrice() const;
    double getDiscount() const;
    double getProfit() const;
    std::string getSellerName() const;
    void displaySale() const;
};

#endif