#include <iostream>
#include <memory>
#include <sqlite3.h>
#include "../Headers/Sale.hpp"
#include "../Headers/Shop.hpp"
#include "../Headers/Product.hpp"

using namespace std;

void create_tables(sqlite3* db) {
    const char* users_table =
        "CREATE TABLE IF NOT EXISTS Users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "salary REAL NOT NULL, "
        "is_admin INTEGER NOT NULL);";

    const char* shops_table =
        "CREATE TABLE IF NOT EXISTS Shops ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL);";

    const char* products_table =
        "CREATE TABLE IF NOT EXISTS Products ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "shop_id INTEGER NOT NULL, "
        "name TEXT NOT NULL, "
        "retail_price REAL NOT NULL, "
        "wholesale_price REAL NOT NULL, "
        "quantity INTEGER NOT NULL, "
        "FOREIGN KEY (shop_id) REFERENCES Shops(id));";

    const char* sales_table =
        "CREATE TABLE IF NOT EXISTS Sales ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "product_id INTEGER NOT NULL, "
        "seller_id INTEGER NOT NULL, "
        "quantity_sold INTEGER NOT NULL, "
        "sale_price REAL NOT NULL, "
        "discount REAL NOT NULL, "
        "profit REAL NOT NULL, "
        "FOREIGN KEY (product_id) REFERENCES Products(id), "
        "FOREIGN KEY (seller_id) REFERENCES Users(id));";

    char* err_msg = nullptr;
    
    int rc = sqlite3_exec(db, users_table, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (Users): " << err_msg << std::endl;
        sqlite3_free(err_msg);
    }

    rc = sqlite3_exec(db, shops_table, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (Shops): " << err_msg << std::endl;
        sqlite3_free(err_msg);
    }

    rc = sqlite3_exec(db, products_table, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (Products): " << err_msg << std::endl;
        sqlite3_free(err_msg);
    }

    rc = sqlite3_exec(db, sales_table, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (Sales): " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Tables created successfully." << std::endl;
    }
}

void insert_seller(sqlite3* db, const string& name, double salary, bool is_admin) {
    const char* sql = "INSERT INTO Users (name, salary, is_admin) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, salary);
    sqlite3_bind_int(stmt, 3, is_admin ? 1 : 0);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Insert failed: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Seller inserted successfully." << std::endl;
    }

    sqlite3_finalize(stmt);
}

void insert_product(sqlite3* db, int shop_id, const string& name, double retail_price, double wholesale_price, int quantity) {
    const char* sql = "INSERT INTO Products (shop_id, name, retail_price, wholesale_price, quantity) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, shop_id);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, retail_price);
    sqlite3_bind_double(stmt, 4, wholesale_price);
    sqlite3_bind_int(stmt, 5, quantity);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Insert failed: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Product inserted successfully." << std::endl;
    }

    sqlite3_finalize(stmt);
}

void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Display shop information (non-admin)" << endl;
    cout << "2. Display shop information (admin)" << endl;
    cout << "3. Remove seller" << endl;
    cout << "4. Remove product" << endl;
    cout << "5. Make a sale" << endl;
    cout << "6. Display sales history" << endl;
    cout << "7. Test overloaded operators and friend functions" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    sqlite3* db;
    
    if (int rc = sqlite3_open("shop_db.db", &db); rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    create_tables(db);

    auto vapeShop = make_unique<Shop>("Scam Judas");

    insert_seller(db, "Danik", 800, false);
    insert_seller(db, "Яна", 1000, true);

    auto seller1 = make_unique<Seller>("Danik", 800);
    auto seller2 = make_unique<Seller>("Яна", 1000, true);
    vapeShop->addSeller(std::move(seller1));
    vapeShop->addSeller(std::move(seller2));

    insert_product(db, 1, "Xros 3 mini", 85, 54, 3);
    insert_product(db, 1, "Hotspot", 15, 8, 60);

    auto product1 = make_unique<Product>("Xros 3 mini", 85, 54, 3);
    auto product2 = make_unique<Product>("Hotspot", 15, 8, 60);
    vapeShop->addProduct(std::move(product1));
    vapeShop->addProduct(std::move(product2));

    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "\nInformation for non-admin user:" << endl;
                vapeShop->displayShop(false);
                break;
            case 2:
                cout << "\nInformation for admin user:" << endl;
                vapeShop->displayShop(true);
                break;
            case 3: {
                cout << "\nEnter the name of the seller to remove: ";
                string sellerName;
                getline(cin, sellerName);
                vapeShop->removeSeller(sellerName);
                break;
            }
            case 4: {
                cout << "\nEnter the name of the product to remove: ";
                string productName;
                getline(cin, productName);
                vapeShop->removeProduct(productName);
                break;
            }
            case 5: {
                cout << "\nEnter the name of the product to sell: ";
                string productName;
                getline(cin, productName);
                cout << "Enter the quantity: ";
                int qty;
                cin >> qty;
                cout << "Enter discount (if any): ";
                double discount;
                cin >> discount;
                vapeShop->makeSale(productName, qty, discount);
                break;
            }
            case 6:
                vapeShop->displaySalesHistory();
                break;
            case 7: {
                cout << "\nTesting overloaded operators and friend functions:" << endl;

                Product tempProduct1("Xros 3 mini", 85, 54, 3);
                Product tempProduct2("Hotspot", 15, 8, 60);

                cout << "Product 1: " << tempProduct1 << endl;
                cout << "Product 2: " << tempProduct2 << endl;

                tempProduct1 = tempProduct1 + 5;
                cout << "Product 1 after adding 5 units: " << tempProduct1 << endl;

                if (compareQuantity(tempProduct1, tempProduct2)) {
                    cout << "Both products have the same quantity." << endl;
                } else {
                    cout << "Products have different quantities." << endl;
                }
                break;
            }
            case 8:
                running = false;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
        if (running && choice != 8) {
            cout << "\nPress Enter to return to the menu...";
            cin.get();
        }
    }    
    sqlite3_close(db);
    return 0;
}