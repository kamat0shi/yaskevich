#include "../Headers/Sale.hpp"

Sale::Sale(const std::string_view productName, int qty, double salePrice, double discount, double profit)
    : productName(productName), quantitySold(qty), salePrice(salePrice), discountApplied(discount), profit(profit) {}

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

void Sale::displaySale() const {
    std::cout << "Товар: " << productName 
              << " | Количество: " << quantitySold 
              << " | Цена продажи: " << salePrice << "р"
              << " | Скидка: " << discountApplied 
              << "% | Прибыль: $" << profit 
              << std::endl;
}