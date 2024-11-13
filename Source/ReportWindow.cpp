#include "../Headers/ReportWindow.hpp"
#include "../Headers/CustomException.hpp"
#include "../Headers/Sale.hpp"
#include "../Headers/Product.hpp"
#include "../Headers/Seller.hpp"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <fstream> 
#include <sqlite3.h>
#include <xlsxwriter.h>

ReportWindow::ReportWindow(QWidget *parent) : QWidget(parent), db(nullptr) {
    if (int rc = sqlite3_open("../shop_db.db", &db); rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных.");
        return;
    }

    QVBoxLayout *layout = new QVBoxLayout(this);

    shopNameInput = new QLineEdit(this);
    shopNameInput->setPlaceholderText("Введите название магазина");
    layout->addWidget(shopNameInput);

    roleFilter = new QLineEdit(this);
    roleFilter->setPlaceholderText("Фильтр по роли (админ, не админ)");
    layout->addWidget(roleFilter);

    minQuantityFilter = new QLineEdit(this);
    minQuantityFilter->setPlaceholderText("Фильтр по минимальному количеству товара");
    layout->addWidget(minQuantityFilter);

    QPushButton *salesHistoryButton = new QPushButton("Загрузить историю продаж", this);
    QPushButton *productListButton = new QPushButton("Загрузить список товаров", this);
    QPushButton *sellerListButton = new QPushButton("Загрузить список продавцов", this);
    QPushButton *fetchShopIdButton = new QPushButton("Получить ID магазина", this);

    layout->addWidget(fetchShopIdButton);
    layout->addWidget(salesHistoryButton);
    layout->addWidget(productListButton);
    layout->addWidget(sellerListButton);

    connect(fetchShopIdButton, &QPushButton::clicked, this, &ReportWindow::fetchShopId);
    connect(salesHistoryButton, &QPushButton::clicked, this, &ReportWindow::downloadSalesHistory);
    connect(productListButton, &QPushButton::clicked, this, &ReportWindow::downloadProductList);
    connect(sellerListButton, &QPushButton::clicked, this, &ReportWindow::downloadSellerList);
}

ReportWindow::~ReportWindow() {
    if (db) {
        sqlite3_close(db);
    }
}

void ReportWindow::fetchShopId() {
    QString shopName = shopNameInput->text();
    if (shopName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название магазина.");
        return;
    }

    const char* sql = "SELECT id FROM Shops WHERE name = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        QMessageBox::critical(this, "Ошибка", "Ошибка при подготовке SQL-запроса: " + QString(sqlite3_errmsg(db)));
        return;
    }

    sqlite3_bind_text(stmt, 1, shopName.toStdString().c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        shop_id = sqlite3_column_int(stmt, 0);
        QMessageBox::information(this, "Успех", "Идентификатор магазина: " + QString::number(shop_id));
    } else {
        QMessageBox::warning(this, "Ошибка", "Магазин не найден.");
    }

    sqlite3_finalize(stmt);
}
void ReportWindow::downloadSalesHistory() {
    if (shop_id == 0) {
        QMessageBox::warning(this, "Ошибка", "Получите идентификатор магазина перед загрузкой.");
        return;
    }

    QFileDialog dialog(this);
    QString filePath = dialog.getSaveFileName(this, "Сохранить отчет о продажах", "", "Excel Files (*.xlsx);;All Files (*.*)");

    if (!filePath.isEmpty()) {
        std::vector<Sale> sales;
        const char* sql = R"(
            SELECT Products.name, Users.name, Sales.quantity_sold, Sales.sale_price, Sales.discount, Sales.profit
            FROM Sales
            JOIN Products ON Sales.product_id = Products.id
            JOIN Users ON Sales.seller_id = Users.id
            WHERE Products.shop_id = ?;
        )";

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, shop_id);
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
            return;
        }

        lxw_workbook  *workbook  = workbook_new(filePath.toStdString().c_str());
        lxw_worksheet *worksheet = workbook_add_worksheet(workbook, nullptr);

        worksheet_write_string(worksheet, 0, 0, "Product Name", nullptr);
        worksheet_write_string(worksheet, 0, 1, "Seller Name", nullptr);
        worksheet_write_string(worksheet, 0, 2, "Quantity Sold", nullptr);
        worksheet_write_string(worksheet, 0, 3, "Sale Price", nullptr);
        worksheet_write_string(worksheet, 0, 4, "Discount", nullptr);
        worksheet_write_string(worksheet, 0, 5, "Profit", nullptr);

        int row = 1;
        for (const auto& sale : sales) {
            worksheet_write_string(worksheet, row, 0, sale.getProductName().c_str(), nullptr);
            worksheet_write_string(worksheet, row, 1, sale.getSellerName().c_str(), nullptr);
            worksheet_write_number(worksheet, row, 2, sale.getQuantitySold(), nullptr);
            worksheet_write_number(worksheet, row, 3, sale.getSalePrice(), nullptr);
            worksheet_write_number(worksheet, row, 4, sale.getDiscount(), nullptr);
            worksheet_write_number(worksheet, row, 5, sale.getProfit(), nullptr);
            row++;
        }

        workbook_close(workbook);

        QMessageBox::information(this, "Загрузка", "Отчет о продажах успешно сохранен в формате XLSX.");
    }
}

void ReportWindow::downloadProductList() {
    if (shop_id == 0) {
        QMessageBox::warning(this, "Ошибка", "Получите идентификатор магазина перед загрузкой.");
        return;
    }

    bool ok;
    int minQuantity = minQuantityFilter->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректное значение для минимального количества.");
        return;
    }

    QFileDialog dialog(this);
    QString filePath = dialog.getSaveFileName(this, "Сохранить список товаров", "", "Excel Files (*.xlsx);;All Files (*.*)");

    if (!filePath.isEmpty()) {
        std::vector<std::unique_ptr<Product>> products;
        const char* sql = "SELECT name, retail_price, wholesale_price, quantity FROM Products WHERE shop_id = ?;";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, shop_id);
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                std::string productName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                double retailPrice = sqlite3_column_double(stmt, 1);
                double wholesalePrice = sqlite3_column_double(stmt, 2);
                int quantity = sqlite3_column_int(stmt, 3);

                if (quantity >= minQuantity) {
                    products.push_back(std::make_unique<Product>(productName, retailPrice, wholesalePrice, quantity));
                }
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Ошибка при загрузке товаров: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        lxw_workbook  *workbook  = workbook_new(filePath.toStdString().c_str());
        lxw_worksheet *worksheet = workbook_add_worksheet(workbook, nullptr);

        worksheet_write_string(worksheet, 0, 0, "Product Name", nullptr);
        worksheet_write_string(worksheet, 0, 1, "Retail Price", nullptr);
        worksheet_write_string(worksheet, 0, 2, "Wholesale Price", nullptr);
        worksheet_write_string(worksheet, 0, 3, "Quantity", nullptr);

        int row = 1;
        for (const auto& product : products) {
            worksheet_write_string(worksheet, row, 0, product->getName().c_str(), nullptr);
            worksheet_write_number(worksheet, row, 1, product->getRetailPrice(), nullptr);
            worksheet_write_number(worksheet, row, 2, product->getWholesalePrice(true), nullptr);
            worksheet_write_number(worksheet, row, 3, product->getQuantity(), nullptr);
            row++;
        }

        workbook_close(workbook);

        QMessageBox::information(this, "Загрузка", "Список товаров успешно сохранен в формате XLSX.");
    }
}

void ReportWindow::downloadSellerList() {
    if (shop_id == 0) {
        QMessageBox::warning(this, "Ошибка", "Получите идентификатор магазина перед загрузкой.");
        return;
    }

    QString roleFilterValue = roleFilter->text().trimmed().toLower();
    bool filterForAdmin = (roleFilterValue == "админ");
    bool filterForNonAdmin = (roleFilterValue == "не админ");

    QFileDialog dialog(this);
    QString filePath = dialog.getSaveFileName(this, "Сохранить список продавцов", "", "Excel Files (*.xlsx);;All Files (*.*)");

    if (!filePath.isEmpty()) {
        std::vector<std::unique_ptr<Seller>> sellers;
        const char* sql = "SELECT name, salary, is_admin FROM Users WHERE shop_id = ?;";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, shop_id);
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                std::string sellerName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                double salary = sqlite3_column_double(stmt, 1);
                bool isAdmin = sqlite3_column_int(stmt, 2);

                if ((filterForAdmin && !isAdmin) || (filterForNonAdmin && isAdmin)) {
                    continue;
                }

                sellers.push_back(std::make_unique<Seller>(sellerName, salary, isAdmin));
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Ошибка при загрузке продавцов: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        lxw_workbook  *workbook  = workbook_new(filePath.toStdString().c_str());
        lxw_worksheet *worksheet = workbook_add_worksheet(workbook, nullptr);

        worksheet_write_string(worksheet, 0, 0, "Seller Name", nullptr);
        worksheet_write_string(worksheet, 0, 1, "Salary", nullptr);
        worksheet_write_string(worksheet, 0, 2, "Is Admin", nullptr);

        int row = 1;
        for (const auto& seller : sellers) {
            worksheet_write_string(worksheet, row, 0, seller->getName().c_str(), nullptr);
            worksheet_write_number(worksheet, row, 1, seller->getSalary(), nullptr);
            worksheet_write_string(worksheet, row, 2, seller->getIsAdmin() ? "Yes" : "No", nullptr);
            row++;
        }

        workbook_close(workbook);

        QMessageBox::information(this, "Загрузка", "Список продавцов успешно сохранен в формате XLSX.");
    }
}