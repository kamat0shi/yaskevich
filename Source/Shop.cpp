#include "../Headers/Sale.hpp"
#include "../Headers/Shop.hpp"

Shop::Shop(const std::string_view n, sqlite3* db) : name(n), db(db) {
    loadSellersFromDB();
    loadProductsFromDB();
}

void Shop::addSeller(std::unique_ptr<Seller> seller) {
    const char* check_sql = "SELECT COUNT(*) FROM Users WHERE name = ?;";
    sqlite3_stmt* check_stmt;
    
    if (sqlite3_prepare_v2(db, check_sql, -1, &check_stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare check statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(check_stmt, 1, seller->getName().c_str(), -1, SQLITE_STATIC);

    int count = 0;
    if (sqlite3_step(check_stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(check_stmt, 0);
    }

    sqlite3_finalize(check_stmt);

    if (count > 0) {
        std::cout << "Продавец с таким именем уже существует в базе данных.\n";
        return;
    }

    const char* sql = "INSERT INTO Users (name, salary, is_admin) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare insert statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, seller->getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, seller->getSalary());
    sqlite3_bind_int(stmt, 3, seller->getIsAdmin() ? 1 : 0);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to insert seller: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Продавец добавлен успешно.\n";
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
        std::cerr << "Ошибка при подготовке удаления продавца: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, sellerName.data(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Ошибка при удалении продавца: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Продавец успешно удален из базы данных.\n";
    }

    sqlite3_finalize(stmt);

   auto new_end = std::ranges::remove_if(sellers, [&](const std::unique_ptr<Seller>& s) {
        return s->getName() == sellerName;
    });

    if (new_end != sellers.end()) {
        sellers.erase(new_end.begin(), new_end.end());
        std::cout << "Продавец удален из списка.\n";
    }
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
    const char* check_sql = "SELECT COUNT(*) FROM Products WHERE name = ?;";
    sqlite3_stmt* check_stmt;
    
    if (sqlite3_prepare_v2(db, check_sql, -1, &check_stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare check statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(check_stmt, 1, product->getName().c_str(), -1, SQLITE_STATIC);

    int count = 0;
    if (sqlite3_step(check_stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(check_stmt, 0);
    }

    sqlite3_finalize(check_stmt);

    if (count > 0) {
        std::cout << "Товар с таким именем уже существует в базе данных.\n";
        return;
    }

    const char* sql = "INSERT INTO Products (shop_id, name, retail_price, wholesale_price, quantity) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare insert statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, 1);
    sqlite3_bind_text(stmt, 2, product->getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, product->getRetailPrice());
    sqlite3_bind_double(stmt, 4, product->getWholesalePrice(true)); 
    sqlite3_bind_int(stmt, 5, product->getQuantity());

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to insert product: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Товар добавлен успешно.\n";
    }

    sqlite3_finalize(stmt);

    products.push_back(std::move(product));
}

void Shop::removeProduct(const std::string_view productName) {
    if (const Product* product = getProduct(productName); !product) {
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

    auto new_end = std::ranges::remove_if(products, [&](const std::unique_ptr<Product>& p) {
        return p->getName() == productName;
    });

    products.erase(new_end.begin(), products.end());

    std::cout << "Товар удален.\n";
}


void Shop::makeSale(const std::string_view productName, int qty, double discount, const std::string& sellerName) {
    Product* product = getProduct(productName);
    const Seller* seller = getSeller(sellerName);  // Указатель на const Seller

    if (!product || !seller) {
        std::cerr << "Продукт или продавец не найдены!" << std::endl;
        return;
    }

    if (product->getQuantity() < qty) {
        std::cerr << "Недостаточно товара на складе!" << std::endl;
        return;
    }

    int productId = product->getIdByName(db, product->getName());
    int sellerId = seller->getIdByName(db, seller->getName());

    if (productId == 0 || sellerId == 0) {
        std::cerr << "Ошибка получения идентификаторов продукта или продавца!" << std::endl;
        return;
    }

    double profit;
    if (discount > 0) {
        profit = product->calculateProfit(qty, discount);
    } else {
        profit = product->calculateProfit(qty);
    }

    double salePrice = product->getRetailPrice() * qty * (1 - discount / 100.0);

    // Обновление количества товара
    if (sqlite3_stmt* updateStmt; sqlite3_prepare_v2(db, "UPDATE Products SET quantity = quantity - ? WHERE id = ?;", -1, &updateStmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(updateStmt, 1, qty);
        sqlite3_bind_int(updateStmt, 2, productId);

        if (sqlite3_step(updateStmt) != SQLITE_DONE) {
            std::cerr << "Ошибка обновления количества товара: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "Количество товара успешно обновлено." << std::endl;
            product->setQuantity(product->getQuantity() - qty);  // Обновляем количество в объекте
        }

        sqlite3_finalize(updateStmt);
    } else {
        std::cerr << "Ошибка подготовки SQL-запроса на обновление товара: " << sqlite3_errmsg(db) << std::endl;
    }

    // Вставка новой продажи
    if (sqlite3_stmt* insertStmt; sqlite3_prepare_v2(db, R"(
        INSERT INTO Sales (product_id, seller_id, quantity_sold, sale_price, discount, profit)
        VALUES (?, ?, ?, ?, ?, ?);
    )", -1, &insertStmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(insertStmt, 1, productId);
        sqlite3_bind_int(insertStmt, 2, sellerId);
        sqlite3_bind_int(insertStmt, 3, qty);
        sqlite3_bind_double(insertStmt, 4, salePrice);
        sqlite3_bind_double(insertStmt, 5, discount);
        sqlite3_bind_double(insertStmt, 6, profit);

        if (sqlite3_step(insertStmt) != SQLITE_DONE) {
            std::cerr << "Ошибка добавления продажи: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "Продажа успешно добавлена в базу данных." << std::endl;
        }

        sqlite3_finalize(insertStmt);
    } else {
        std::cerr << "Ошибка подготовки SQL-запроса для продажи: " << sqlite3_errmsg(db) << std::endl;
    }

    std::cout << "Продажа завершена! Прибыль: $" << profit << std::endl;
}

void Shop::displayShop(bool isAdmin) const {
    std::cout << "Магазин: " << name << std::endl;
    std::cout << "Продавцы:" << std::endl;
    
    for (const auto& seller : sellers) {
        std::cout << "Продавец: " << seller->getName() 
                  << ", Зарплата: " << seller->getSalary() 
                  << ", Роль: " << seller->getRole()
                  << std::endl;
    }

    std::cout << "Товары:" << std::endl;
    
    for (const auto& product : products) {
        product->displayProduct(isAdmin);
    }
}

void Shop::displaySalesHistory() const {
    std::cout << "История продаж: " << std::endl;

    const char* sql = R"(
        SELECT Products.name, Users.name, Sales.quantity_sold, Sales.sale_price, Sales.discount, Sales.profit
        FROM Sales
        JOIN Products ON Sales.product_id = Products.id
        JOIN Users ON Sales.seller_id = Users.id;
    )";
    
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string productName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string sellerName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int quantitySold = sqlite3_column_int(stmt, 2);
            double salePrice = sqlite3_column_double(stmt, 3);
            double discount = sqlite3_column_double(stmt, 4);
            double profit = sqlite3_column_double(stmt, 5);

            std::cout << "Продукт: " << productName 
                      << " | Продавец: " << sellerName
                      << " | Количество: " << quantitySold 
                      << " | Цена продажи: " << salePrice << "р"
                      << " | Скидка: " << discount 
                      << "% | Прибыль: $" << profit 
                      << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Ошибка при загрузке продаж: " << sqlite3_errmsg(db) << std::endl;
    }
}

void Shop::loadSellersFromDB() {
    const char* sql = "SELECT name, salary, is_admin FROM Users;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            double salary = sqlite3_column_double(stmt, 1);
            bool isAdmin = sqlite3_column_int(stmt, 2);

            std::cout << "Загружен продавец: " << name << ", зарплата: " << salary << std::endl;

            sellers.push_back(std::make_unique<Seller>(name, salary, isAdmin));
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Ошибка при загрузке продавцов: " << sqlite3_errmsg(db) << std::endl;
    }
}

void Shop::loadProductsFromDB() {
    const char* sql = "SELECT name, retail_price, wholesale_price, quantity FROM Products;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            double retailPrice = sqlite3_column_double(stmt, 1);
            double wholesalePrice = sqlite3_column_double(stmt, 2);
            int quantity = sqlite3_column_int(stmt, 3);

            products.push_back(std::make_unique<Product>(name, retailPrice, wholesalePrice, quantity));
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Ошибка при загрузке товаров: " << sqlite3_errmsg(db) << std::endl;
    }
}

const std::vector<std::unique_ptr<Seller>>& Shop::getSellers() const {
    return sellers;
}

const std::vector<std::unique_ptr<Product>>& Shop::getProducts() const {
    return products;
}

std::vector<Sale> Shop::getSalesHistory() const {
    std::vector<Sale> sales;

    const char* sql = R"(
        SELECT Products.name, Users.name, Sales.quantity_sold, Sales.sale_price, Sales.discount, Sales.profit
        FROM Sales
        JOIN Products ON Sales.product_id = Products.id
        JOIN Users ON Sales.seller_id = Users.id;
    )";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string productName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string sellerName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int quantitySold = sqlite3_column_int(stmt, 2);
            double salePrice = sqlite3_column_double(stmt, 3);
            double discount = sqlite3_column_double(stmt, 4);
            double profit = sqlite3_column_double(stmt, 5);

            sales.emplace_back(productName, quantitySold, salePrice, discount, profit);
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Ошибка при загрузке продаж: " << sqlite3_errmsg(db) << std::endl;
    }

    return sales;
}