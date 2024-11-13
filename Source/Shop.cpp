#include "../Headers/Sale.hpp"
#include "../Headers/Shop.hpp"
#include "../Headers/Sale.hpp" 
#include "../Headers/Utility.hpp"
#include "../Headers/CustomException.hpp"

Shop::Shop(const std::string_view n, sqlite3* db) : name(n), db(db) {
    try {
        fetchShopIdByName();
        loadSellersFromDB();
        loadProductsFromDB();
    } catch (const CustomException& e) {
        std::cerr << "Ошибка при инициализации магазина: " << e.what() << std::endl;
    }
}

void Shop::fetchShopIdByName() {
    const char* check_sql = "SELECT id FROM Shops WHERE name = ?;";
    sqlite3_stmt* check_stmt;
    
    if (sqlite3_prepare_v2(db, check_sql, -1, &check_stmt, nullptr) != SQLITE_OK) {
        throw CustomException("Ошибка при подготовке SQL-запроса: " + std::string(sqlite3_errmsg(db)));
    }
    
    sqlite3_bind_text(check_stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(check_stmt) == SQLITE_ROW) {
        shop_id = sqlite3_column_int(check_stmt, 0);
        std::cout << "Идентификатор магазина " << name << " установлен: " << shop_id << std::endl;
    } else {
        sqlite3_finalize(check_stmt);

        const char* insert_sql = "INSERT INTO Shops (name) VALUES (?);";
        sqlite3_stmt* insert_stmt;
        
        if (sqlite3_prepare_v2(db, insert_sql, -1, &insert_stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Ошибка при подготовке SQL-запроса для вставки: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        sqlite3_bind_text(insert_stmt, 1, name.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(insert_stmt) == SQLITE_DONE) {
            shop_id = sqlite3_last_insert_rowid(db);
            std::cout << "Создан новый магазин: " << name << " с идентификатором " << shop_id << std::endl;
        } else {
            std::cerr << "Ошибка при вставке нового магазина: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(insert_stmt);
    }
}

void Shop::addSeller(std::unique_ptr<Seller> seller) {
    const char* check_sql = "SELECT COUNT(*) FROM Users WHERE name = ? AND shop_id = ?;";
    sqlite3_stmt* check_stmt;

    if (sqlite3_prepare_v2(db, check_sql, -1, &check_stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка SQL: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(check_stmt, 1, seller->getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(check_stmt, 2, shop_id);

    int count = 0;
    if (sqlite3_step(check_stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(check_stmt, 0);
    }
    sqlite3_finalize(check_stmt);

    if (count > 0) {
        std::cout << "Продавец уже существует.\n";
        return;
    }

    const char* sql = "INSERT INTO Users (name, salary, is_admin, shop_id) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка SQL: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, seller->getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, seller->getSalary());
    sqlite3_bind_int(stmt, 3, seller->getIsAdmin() ? 1 : 0);
    sqlite3_bind_int(stmt, 4, shop_id);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        sellers.addItem(std::move(seller));
        std::cout << "Продавец добавлен.\n";
    } else {
        std::cerr << "Ошибка при добавлении продавца: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

void Shop::removeSeller(const std::string_view sellerName) {
    if (const Seller* seller = sellers.findItem(std::string(sellerName)); !seller) {
        std::cout << "Продавец не найден.\n";
        return;
    }

    const char* sql = "DELETE FROM Users WHERE name = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка SQL: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, sellerName.data(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        sellers.removeItem(std::string(sellerName));
        std::cout << "Продавец удалён.\n";
    } else {
        std::cerr << "Ошибка при удалении продавца: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

Seller* Shop::getSeller(const std::string_view sellerName) {
    return sellers.findItem(std::string(sellerName));
}

Product* Shop::getProduct(const std::string_view productName) {
    return products.findItem(std::string(productName));
}

void Shop::addProduct(std::unique_ptr<Product> product) {
    const char* check_sql = "SELECT COUNT(*) FROM Products WHERE name = ? AND shop_id = ?;";
    sqlite3_stmt* check_stmt;

    if (sqlite3_prepare_v2(db, check_sql, -1, &check_stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка SQL: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(check_stmt, 1, product->getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(check_stmt, 2, shop_id);

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
        std::cerr << "Ошибка SQL: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, shop_id);
    sqlite3_bind_text(stmt, 2, product->getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, product->getRetailPrice());
    sqlite3_bind_double(stmt, 4, product->getWholesalePrice(true));
    sqlite3_bind_int(stmt, 5, product->getQuantity());

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        products.addItem(std::move(product)); 
        std::cout << "Товар добавлен успешно.\n";
    } else {
        std::cerr << "Ошибка при добавлении товара: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

void Shop::removeProduct(const std::string_view productName) {
    if (const Product* product = getProduct(productName); !product) {
        std::cout << "Товар не найден.\n";
        return;
    }

    const char* sql = "DELETE FROM Products WHERE name = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса на удаление: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, productName.data(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Ошибка при удалении товара: " << sqlite3_errmsg(db) << std::endl;
    } else {
        products.removeItem(std::string(productName));
        std::cout << "Товар удален.\n";
    }

    sqlite3_finalize(stmt);
}


void Shop::makeSale(const std::string_view productName, int qty, double discount, const std::string& sellerName) {
    try {
        Product* product = getProduct(productName);
        const Seller* seller = getSeller(sellerName);

        if (!product || !seller) {
            throw CustomException("Продукт или продавец не найдены!");
        }

        if (product->getQuantity() < qty) {
            throw CustomException("Недостаточно товара на складе!");
        }

        int productId = product->getIdByName(db, product->getName());
        int sellerId = seller->getIdByName(db, seller->getName());

        if (productId == 0 || sellerId == 0) {
            throw CustomException("Ошибка получения идентификаторов продукта или продавца!");
        }

        double profit;
        if (discount > 0) {
            profit = product->calculateProfit(qty, discount);
        } else {
            profit = product->calculateProfit(qty);
        }

        double salePrice = product->getRetailPrice() * qty * (1 - discount / 100.0);

        sqlite3_stmt* updateStmt;
        if (sqlite3_prepare_v2(db, "UPDATE Products SET quantity = quantity - ? WHERE id = ?;", -1, &updateStmt, nullptr) != SQLITE_OK) {
            throw CustomException("Ошибка подготовки SQL-запроса на обновление товара: " + std::string(sqlite3_errmsg(db)));
        }

        sqlite3_bind_int(updateStmt, 1, qty);
        sqlite3_bind_int(updateStmt, 2, productId);

        if (sqlite3_step(updateStmt) != SQLITE_DONE) {
            sqlite3_finalize(updateStmt);
            throw CustomException("Ошибка обновления количества товара: " + std::string(sqlite3_errmsg(db)));
        } else {
            product->setQuantity(product->getQuantity() - qty);
        }

        sqlite3_finalize(updateStmt);

        sqlite3_stmt* insertStmt;
        if (sqlite3_prepare_v2(db, R"(
            INSERT INTO Sales (product_id, seller_id, quantity_sold, sale_price, discount, profit)
            VALUES (?, ?, ?, ?, ?, ?);
        )", -1, &insertStmt, nullptr) != SQLITE_OK) {
            throw CustomException("Ошибка подготовки SQL-запроса для продажи: " + std::string(sqlite3_errmsg(db)));
        }

        sqlite3_bind_int(insertStmt, 1, productId);
        sqlite3_bind_int(insertStmt, 2, sellerId);
        sqlite3_bind_int(insertStmt, 3, qty);
        sqlite3_bind_double(insertStmt, 4, salePrice);
        sqlite3_bind_double(insertStmt, 5, discount);
        sqlite3_bind_double(insertStmt, 6, profit);

        if (sqlite3_step(insertStmt) != SQLITE_DONE) {
            sqlite3_finalize(insertStmt);
            throw CustomException("Ошибка добавления продажи: " + std::string(sqlite3_errmsg(db)));
        }

        sqlite3_finalize(insertStmt);

    } catch (const CustomException& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
        throw;
    }
}

void Shop::displayShop(bool isAdmin) const {
    std::cout << "Магазин: " << name << std::endl;
    std::cout << "Продавцы:" << std::endl;
    sellers.displayAll(); 

    std::cout << "Товары:" << std::endl;
    products.displayAll(isAdmin);
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
    const char* sql = "SELECT name, salary, is_admin FROM Users WHERE shop_id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, shop_id);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string sellerName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));  
            double salary = sqlite3_column_double(stmt, 1);
            bool isAdmin = sqlite3_column_int(stmt, 2);
            std::cout << "Загружен продавец: " << sellerName << ", зарплата: " << salary << std::endl;
            sellers.addItem(std::make_unique<Seller>(sellerName, salary, isAdmin));
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Ошибка при загрузке продавцов: " << sqlite3_errmsg(db) << std::endl;
    }
}

void Shop::loadProductsFromDB() {
    const char* sql = "SELECT name, retail_price, wholesale_price, quantity FROM Products WHERE shop_id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, shop_id);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string productName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)); 
            double retailPrice = sqlite3_column_double(stmt, 1);
            double wholesalePrice = sqlite3_column_double(stmt, 2);
            int quantity = sqlite3_column_int(stmt, 3);
            products.addItem(std::make_unique<Product>(productName, retailPrice, wholesalePrice, quantity));
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Ошибка при загрузке товаров: " << sqlite3_errmsg(db) << std::endl;
    }
}

const std::vector<std::unique_ptr<Seller>>& Shop::getSellers() const {
    return sellers.getItems();
}

const std::vector<std::unique_ptr<Product>>& Shop::getProducts() const {
    return products.getItems();
}

std::vector<Sale> Shop::getSalesHistory() const {
    std::vector<Sale> sales;
    const char* sql = R"(
        SELECT Products.name, Users.name, Sales.quantity_sold, Sales.sale_price, Sales.discount, Sales.profit
        FROM Sales
        JOIN Products ON Sales.product_id = Products.id
        JOIN Users ON Sales.seller_id = Users.id;
    )";
    
    if (sqlite3_stmt* stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {  
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string productName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string sellerName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int quantitySold = sqlite3_column_int(stmt, 2);
            double salePrice = sqlite3_column_double(stmt, 3);
            double discount = sqlite3_column_double(stmt, 4);
            double profit = sqlite3_column_double(stmt, 5);

            sales.emplace_back(productName, quantitySold, salePrice, discount, profit, sellerName);
        }
        sqlite3_finalize(stmt);  
    } else {
        std::cerr << "Ошибка при загрузке продаж: " << sqlite3_errmsg(db) << std::endl;
    }
    return sales;  
}