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

int Product::getIdByName(sqlite3* db, const std::string& productName) const { 
    int productId = 0;
    const char* sql = "SELECT id FROM Products WHERE name = ?;";

    if (sqlite3_stmt* stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, productName.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            productId = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Ошибка при получении product_id: " << sqlite3_errmsg(db) << std::endl;
    }

    return productId;
}

double Product::calculateProfit(int qty) const {
    return retailPrice * qty - wholesalePrice * qty;
}

double Product::calculateProfit(int qty, double discount) const { 
    double discountedPrice = retailPrice * (1 - discount / 100.0);
    return discountedPrice * qty - wholesalePrice * qty;
}

void Product::displayInfo(bool isAdmin) const {
    std::cout << "Название: " << name << ", Розничная цена: " << retailPrice 
              << ", Количество: " << quantity << std::endl;
    if (isAdmin) {
        std::cout << "Оптовая цена: " << wholesalePrice << std::endl;
    }
}

std::string Product::getInfo(bool isAdmin) const {
    std::stringstream ss;
    ss << "Название: " << name << ", Розничная цена: " << retailPrice << ", Количество: " << quantity;
    if (isAdmin) {
        ss << ", Оптовая цена: " << wholesalePrice;
    }
    return ss.str();
}
