#include <iostream>
#include <iomanip>
#include <sqlite3.h>

// Функция для вывода пользователей в виде таблицы
void select_all_users(sqlite3* db) {
    const char* sql = "SELECT id, name, salary, is_admin FROM Users;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << std::setw(5) << "ID" << std::setw(15) << "Name" 
              << std::setw(10) << "Salary" << std::setw(10) << "Admin" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double salary = sqlite3_column_double(stmt, 2);
        int is_admin = sqlite3_column_int(stmt, 3);

        std::cout << std::setw(5) << id 
                  << std::setw(15) << name 
                  << std::setw(10) << salary 
                  << std::setw(10) << (is_admin ? "Yes" : "No") << std::endl;
    }

    sqlite3_finalize(stmt);
}

// Функция для вывода товаров в виде таблицы
void select_all_products(sqlite3* db) {
    const char* sql = "SELECT id, name, retail_price, wholesale_price, quantity FROM Products;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << std::setw(5) << "ID" << std::setw(20) << "Name" 
              << std::setw(15) << "Retail Price" << std::setw(15) << "Wholesale Price" 
              << std::setw(10) << "Quantity" << std::endl;
    std::cout << std::string(65, '-') << std::endl;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double retail_price = sqlite3_column_double(stmt, 2);
        double wholesale_price = sqlite3_column_double(stmt, 3);
        int quantity = sqlite3_column_int(stmt, 4);

        std::cout << std::setw(5) << id 
                  << std::setw(20) << name 
                  << std::setw(15) << retail_price 
                  << std::setw(15) << wholesale_price 
                  << std::setw(10) << quantity << std::endl;
    }

    sqlite3_finalize(stmt);
}

// Функция для вывода продаж в виде таблицы
void select_all_sales(sqlite3* db) {
    const char* sql = "SELECT id, product_id, seller_id, quantity_sold, sale_price, discount, profit FROM Sales;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << std::setw(5) << "ID" << std::setw(12) << "Product ID" 
              << std::setw(12) << "Seller ID" << std::setw(15) << "Quantity Sold" 
              << std::setw(12) << "Sale Price" << std::setw(10) << "Discount" 
              << std::setw(10) << "Profit" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int product_id = sqlite3_column_int(stmt, 1);
        int seller_id = sqlite3_column_int(stmt, 2);
        int quantity_sold = sqlite3_column_int(stmt, 3);
        double sale_price = sqlite3_column_double(stmt, 4);
        double discount = sqlite3_column_double(stmt, 5);
        double profit = sqlite3_column_double(stmt, 6);

        std::cout << std::setw(5) << id 
                  << std::setw(12) << product_id 
                  << std::setw(12) << seller_id 
                  << std::setw(15) << quantity_sold 
                  << std::setw(12) << sale_price 
                  << std::setw(10) << discount 
                  << std::setw(10) << profit << std::endl;
    }

    sqlite3_finalize(stmt);
}

// Функция для очистки всех таблиц
void clear_all_tables(sqlite3* db) {
    const char* tables[] = {"Users", "Products", "Sales"};
    for (const char* table : tables) {
        std::string sql = "DELETE FROM " + std::string(table) + ";";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Failed to prepare delete statement for " << table << ": " 
                      << sqlite3_errmsg(db) << std::endl;
            continue;
        }

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Failed to clear table " << table << ": " 
                      << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
    }
    std::cout << "All tables cleared.\n";
}

void displayMenu() {
    std::cout << "1. Display all users\n";
    std::cout << "2. Display all products\n";
    std::cout << "3. Display all sales\n";
    std::cout << "4. Clear all tables\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    sqlite3* db;
    if (int rc = sqlite3_open("shop_db.db", &db); rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "\nUsers Table:\n";
                select_all_users(db);
                break;
            case 2:
                std::cout << "\nProducts Table:\n";
                select_all_products(db);
                break;
            case 3:
                std::cout << "\nSales Table:\n";
                select_all_sales(db);
                break;
            case 4:
                clear_all_tables(db);
                break;
            case 5:
                running = false;
                break;
            default:
                std::cout << "Invalid choice, try again.\n";
        }
        std::cout << "\n";
    }

    sqlite3_close(db);
    return 0;
}