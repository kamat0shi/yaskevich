#include "../Headers/Shop.hpp"
#include "../Headers/Sale.hpp"

Shop::Shop(const std::string_view n, sqlite3* db) : name(n), db(db) {}

void Shop::addSeller(std::unique_ptr<Seller> seller) {
    const char* sql = "INSERT INTO Users (name, salary, is_admin) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, seller->getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, seller->getSalary());
    sqlite3_bind_int(stmt, 3, seller->getIsAdmin() ? 1 : 0);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to insert seller: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

    sellers.push_back(std::move(seller));
}

void Shop::removeSeller(const std::string_view sellerName) {
    if (const Seller* seller = getSeller(sellerName); !seller) {
        std::cout << "Продавец не найден.\n";
        return;
    }

    const char* sql = "DELETE FROM Users WHERE name = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare delete statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, sellerName.data(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to delete seller: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

    auto it = std::remove_if(sellers.begin(), sellers.end(), [&](const std::unique_ptr<Seller>& s) {
        return s->getName() == sellerName;
    });
    sellers.erase(it, sellers.end());

    std::cout << "Продавец удален.\n";
}

Seller* Shop::getSeller(const std::string_view sellerName) {
    for (const auto& seller : sellers) {
        if (seller->getName() == sellerName) {
            return seller.get();
        }
    }
    return nullptr;
}

Product* Shop::getProduct(const std::string_view productName) {
    for (const auto& product : products) {
        if (product->getName() == productName) {
            return product.get();
        }
    }
    return nullptr;
}

void Shop::addProduct(std::unique_ptr<Product> product) {
    const char* sql = "INSERT INTO Products (shop_id, name, retail_price, wholesale_price, quantity) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, 1);
    sqlite3_bind_text(stmt, 2, product->getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, product->getRetailPrice());
    sqlite3_bind_double(stmt, 4, product->getWholesalePrice(true)); 
    sqlite3_bind_int(stmt, 5, product->getQuantity());

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to insert product: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

    products.push_back(std::move(product));
}

void Shop::removeProduct(const std::string_view productName) {
    if (Product* product = getProduct(productName); !product) {
        std::cout << "Товар не найден.\n";
        return;
    }

    const char* sql = "DELETE FROM Products WHERE name = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare delete statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, productName.data(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to delete product: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

    auto it = std::remove_if(products.begin(), products.end(), [&](const std::unique_ptr<Product>& p) {
        return p->getName() == productName;
    });
    products.erase(it, products.end());

    std::cout << "Товар удален.\n";
}

void Shop::makeSale(const std::string_view productName, int qty, double discount) {
    Product* product = getProduct(productName);
    if (product && product->getQuantity() >= qty) {
        double retailPrice = product->getRetailPrice();
        double wholesalePrice = product->getWholesalePrice(true); 
        double salePrice = retailPrice * qty * (1 - discount / 100.0);
        double profit = (salePrice - wholesalePrice * qty);

        product->reduceQuantity(qty);

        const char* sql = "INSERT INTO Sales (product_id, seller_id, quantity_sold, sale_price, discount, profit) VALUES (?, ?, ?, ?, ?, ?);";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Failed to prepare insert sale statement: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        sqlite3_bind_int(stmt, 1, 1);  
        sqlite3_bind_int(stmt, 2, 1);  
        sqlite3_bind_int(stmt, 3, qty);
        sqlite3_bind_double(stmt, 4, salePrice);
        sqlite3_bind_double(stmt, 5, discount);
        sqlite3_bind_double(stmt, 6, profit);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Failed to insert sale: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);

        salesHistory.emplace_back(productName, qty, salePrice, discount, profit);

        std::cout << "Продажа завершена! Прибыль: $" << profit << std::endl;
    } else {
        std::cout << "Товар не найден или недостаточно количества!" << std::endl;
    }
}

void Shop::displayShop(bool isAdmin) const {
    std::cout << "Магазин: " << name << std::endl;
    std::cout << "Продавцы:" << std::endl;
    for (const auto& seller : sellers) {
        seller->displaySeller();
    }
    std::cout << "Товары:" << std::endl;
    for (const auto& product : products) {
        product->displayProduct(isAdmin);
    }
}

void Shop::displaySalesHistory() const {
    std::cout << "История продаж: " << std::endl;
    for (const auto& sale : salesHistory) {
        sale.displaySale();
    }
}