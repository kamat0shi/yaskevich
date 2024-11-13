#include "../Headers/Sale.hpp"

Sale::Sale(const std::string& productName, int qty, double salePrice, double discount, double profit, const std::string& sellerName)
    : productName(productName), quantitySold(qty), salePrice(salePrice), discountApplied(discount), profit(profit), sellerName(sellerName) {}

std::string Sale::getProductName() const {
    return productName;
}


int Sale::getQuantitySold() const {
    return quantitySold;
}

double Sale::getSalePrice() const {
    return salePrice;
}

double Sale::getDiscount() const {
    return discountApplied;
}

double Sale::getProfit() const {
    return profit;
}

std::string Sale::getSellerName() const {
    return sellerName;
}

void Sale::displaySale() const {
    std::cout << "Товар: " << productName 
              << " | Количество: " << quantitySold 
              << " | Цена продажи: " << salePrice << "р"
              << " | Скидка: " << discountApplied 
              << "% | Прибыль: $" << profit 
              << std::endl;
}