#include "Sale.hpp"

Sale::Sale(const std::string_view productName, int qty, double salePrice, double discount, double profit)
    : productName(productName), quantitySold(qty), salePrice(salePrice), discountApplied(discount), profit(profit) {}

void Sale::displaySale() const {
    std::cout << "Товар: " << productName 
              << " | Количество: " << quantitySold 
              << " | Цена продажи: " << salePrice << "р"
              << " | Скидка: " << discountApplied 
              << "% | Прибыль: $" << profit 
              << std::endl;
}