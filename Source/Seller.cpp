#include "../Headers/Seller.hpp"
#include <iostream>
#include <sqlite3.h>


Seller::Seller(const std::string_view n, double s, bool admin)
    : name(n), salary(s), isAdmin(admin) {}

void Seller::setName(const std::string_view n) { name = n; }
void Seller::setSalary(double s) { salary = s; }

std::string Seller::getName() const { return name; }
double Seller::getSalary() const { return salary; }
bool Seller::getIsAdmin() const { return isAdmin; }

std::string Seller::getRole() const {
    return "Seller";
}

void Seller::displayInfo() const {
    std::cout << "Имя: " << name << ", Зарплата: " << salary;
    if (isAdmin) {
        std::cout << " (Администратор)";
    }
    std::cout << std::endl;
}

int Seller::getIdByName(sqlite3* db, const std::string& sellerName) const {
    int sellerId = 0;
    const char* sql = "SELECT id FROM Users WHERE name = ?;";

    if (sqlite3_stmt* stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, sellerName.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            sellerId = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Ошибка при получении seller_id: " << sqlite3_errmsg(db) << std::endl;
    }

    return sellerId;
}

std::string Seller::getInfo() const {
    std::stringstream ss;
    ss << "Имя: " << name << ", Зарплата: " << salary;
    if (isAdmin) {
        ss << " (Администратор)";
    }
    return ss.str();
}