#include "../Headers/Product.hpp"

Product::Product(const std::string_view n, double rPrice, double wPrice, int q)
    : name(n), retailPrice(rPrice), wholesalePrice(wPrice), quantity(q) {}

void Product::setName(const std::string_view n) { name = n; }
void Product::setRetailPrice(double rPrice) { retailPrice = rPrice; }
void Product::setWholesalePrice(double wPrice) { wholesalePrice = wPrice; }
void Product::setQuantity(int q) { quantity = q; }

std::string Product::getName() const { return name; }
double Product::getRetailPrice() const { return retailPrice; }
double Product::getWholesalePrice(bool isAdmin) const {
    if (isAdmin) {
        return wholesalePrice;
    } else {
        std::cout << "Доступ запрещен: только администратор может просматривать оптовую цену!" << std::endl;
        return -1;
    }
}
int Product::getQuantity() const { return quantity; }

void Product::displayProduct(bool isAdmin) const {
    std::cout << "Название: " << name << ", Розничная цена: " << retailPrice << ", Количество: " << quantity << std::endl;
    if (isAdmin) {
        std::cout << "Оптовая цена: " << wholesalePrice << std::endl;
    }
}

void Product::reduceQuantity(int qty) {
    if (qty <= quantity) {
        quantity -= qty;
    } else {
        std::cout << "Not enough stock available!" << std::endl;
    }
}

bool compareQuantity(const Product& p1, const Product& p2) {
    return p1.quantity == p2.quantity;
}

bool Product::operator==(const Product& other) const {
    return (name == other.name && retailPrice == other.retailPrice &&
            wholesalePrice == other.wholesalePrice && quantity == other.quantity);
}

Product& Product::operator+(int additionalQty) {
    this->quantity += additionalQty;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Product& product) {
    os << "Название: " << product.name 
       << ", Розничная цена: " << product.retailPrice 
       << ", Количество: " << product.quantity;
    return os;
}