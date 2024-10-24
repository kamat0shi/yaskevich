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

public:
    Sale(const std::string_view productName, int qty, double salePrice, double discount, double profit); 

    std::string getProductName() const;
    int getQuantitySold() const;
    double getSalePrice() const;
    double getDiscount() const;
    double getProfit() const;

    void displaySale() const;
};

#endif