#include "../Headers/Mainwindow.hpp"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QTextEdit>
#include <QInputDialog>
#include <QLineEdit>
#include <iostream>
#include <memory>
#include <sqlite3.h>
#include <string>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    if (int rc = sqlite3_open("../shop_db.db", &db); rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    vapeShop = std::make_unique<Shop>("Scam Judas", db);
    
    auto centralWidget = std::make_unique<QWidget>(this);
    
    // Используем std::make_unique вместо new для layout
    auto layout = std::make_unique<QVBoxLayout>(centralWidget.get());

    auto label = std::make_unique<QLabel>("Меню магазина", this);
    layout->addWidget(label.get());

    auto button1 = std::make_unique<QPushButton>("Отобразить информацию о магазине (не админ)", this);
    auto button2 = std::make_unique<QPushButton>("Отобразить информацию о магазине (админ)", this);
    auto button3 = std::make_unique<QPushButton>("Удалить продавца", this);
    auto button4 = std::make_unique<QPushButton>("Удалить продукт", this);
    auto button5 = std::make_unique<QPushButton>("Совершить продажу", this);
    auto button6 = std::make_unique<QPushButton>("Добавить продавца", this);  
    auto button7 = std::make_unique<QPushButton>("Добавить продукт", this);   
    auto button8 = std::make_unique<QPushButton>("История продаж", this);
    
    layout->addWidget(button1.get());
    layout->addWidget(button2.get());
    layout->addWidget(button3.get());
    layout->addWidget(button4.get());
    layout->addWidget(button5.get());
    layout->addWidget(button6.get());
    layout->addWidget(button7.get());
    layout->addWidget(button8.get());

    infoDisplay = std::make_unique<QTextEdit>(this);
    infoDisplay->setReadOnly(true); 
    layout->addWidget(infoDisplay.get());

    setCentralWidget(centralWidget.release());

    connect(button1.get(), &QPushButton::clicked, this, &MainWindow::displayShopNonAdmin);
    connect(button2.get(), &QPushButton::clicked, this, &MainWindow::displayShopAdmin);
    connect(button3.get(), &QPushButton::clicked, this, &MainWindow::removeSeller);
    connect(button4.get(), &QPushButton::clicked, this, &MainWindow::removeProduct);
    connect(button5.get(), &QPushButton::clicked, this, &MainWindow::makeSale);
    connect(button6.get(), &QPushButton::clicked, this, &MainWindow::addSeller);  
    connect(button7.get(), &QPushButton::clicked, this, &MainWindow::addProduct);
    connect(button8.get(), &QPushButton::clicked, this, &MainWindow::displaySalesHistory);
}

MainWindow::~MainWindow() {
    sqlite3_close(db);  
}

void MainWindow::displayShopNonAdmin() {
    QString info;
    info += "Магазин: Scam Judas\n";
    
    info += "Продавцы:\n";
    for (const auto& seller : vapeShop->getSellers()) {
        info += QString("Продавец: %1, Зарплата: %2, Роль: %3\n")
                   .arg(QString::fromStdString(seller->getName()))
                   .arg(seller->getSalary())
                   .arg(QString::fromStdString(seller->getRole())); 
    }

    info += "\nТовары:\n";
    for (const auto& product : vapeShop->getProducts()) {
        info += QString("Товар: %1, Цена: %2, Количество: %3\n")
                   .arg(QString::fromStdString(product->getName()))
                   .arg(product->getRetailPrice())
                   .arg(product->getQuantity());
    }

    infoDisplay->setText(info);
}

void MainWindow::displayShopAdmin() {
    QString info;
    info += "Магазин (админ): Scam Judas\n";
    
    info += "\nПродавцы (админ):\n";
    for (const auto& seller : vapeShop->getSellers()) {
        info += QString("Продавец: %1, Зарплата: %2, Админ: %3, Роль: %4\n")
                   .arg(QString::fromStdString(seller->getName()))
                   .arg(seller->getSalary())
                   .arg(seller->getIsAdmin() ? "Да" : "Нет")
                   .arg(QString::fromStdString(seller->getRole())); 
    }

    info += "\nПродукты (админ):\n";
    for (const auto& product : vapeShop->getProducts()) {
        info += QString("Продукт: %1, Цена: %2, Количество: %3, Оптовая цена: %4\n")
                   .arg(QString::fromStdString(product->getName()))
                   .arg(product->getRetailPrice())
                   .arg(product->getQuantity())
                   .arg(product->getWholesalePrice(true));
    }

    infoDisplay->setText(info);
}
void MainWindow::addSeller() {
    bool ok;
    QString name = QInputDialog::getText(this, tr("Добавить продавца"),
                                         tr("Имя продавца:"), QLineEdit::Normal,
                                         "", &ok);
    if (!ok || name.isEmpty()) return;

    double salary = QInputDialog::getDouble(this, tr("Зарплата"), tr("Введите зарплату:"), 0, 0, 10000, 2, &ok);
    if (!ok) return;

    bool isAdmin = QInputDialog::getInt(this, tr("Администратор?"), tr("Введите 1, если администратор, 0 если нет:"), 0, 0, 1, 1, &ok);
    if (!ok) return;

    
    vapeShop->addSeller(std::make_unique<Seller>(name.toStdString(), salary, isAdmin));
    QMessageBox::information(this, "Добавление", "Продавец успешно добавлен.");
}


void MainWindow::removeSeller() {
    bool ok;
    QString sellerName = QInputDialog::getText(this, tr("Удалить продавца"),
                                               tr("Имя продавца:"), QLineEdit::Normal,
                                               "", &ok);
    if (ok && !sellerName.isEmpty()) {
        vapeShop->removeSeller(sellerName.toStdString()); 
        QMessageBox::information(this, "Удаление", QString("Продавец %1 удален.").arg(sellerName));
    } else {
        QMessageBox::warning(this, "Ошибка", "Имя продавца не введено.");
    }
}

void MainWindow::addProduct() {
    bool ok;
    QString name = QInputDialog::getText(this, tr("Добавить продукт"),
                                         tr("Имя продукта:"), QLineEdit::Normal,
                                         "", &ok);
    if (!ok || name.isEmpty()) return;

    double retailPrice = QInputDialog::getDouble(this, tr("Розничная цена"), tr("Введите розничную цену:"), 0, 0, 10000, 2, &ok);
    if (!ok) return;

    double wholesalePrice = QInputDialog::getDouble(this, tr("Оптовая цена"), tr("Введите оптовую цену:"), 0, 0, 10000, 2, &ok);
    if (!ok) return;

    int quantity = QInputDialog::getInt(this, tr("Количество"), tr("Введите количество товара:"), 1, 1, 1000, 1, &ok);
    if (!ok) return;

    vapeShop->addProduct(std::make_unique<Product>(name.toStdString(), retailPrice, wholesalePrice, quantity));
    QMessageBox::information(this, "Добавление", "Продукт успешно добавлен.");
}

void MainWindow::removeProduct() {
    bool ok;
    QString productName = QInputDialog::getText(this, tr("Удалить продукт"),
                                                tr("Имя продукта:"), QLineEdit::Normal,
                                                "", &ok);
    if (ok && !productName.isEmpty()) {
        vapeShop->removeProduct(productName.toStdString()); 
        QMessageBox::information(this, "Удаление", QString("Продукт %1 удален.").arg(productName));
    } else {
        QMessageBox::warning(this, "Ошибка", "Имя продукта не введено.");
    }
}

void MainWindow::makeSale() {
    bool ok;
    
    QString productName = QInputDialog::getText(this, tr("Продажа товара"),
                                                tr("Имя продукта:"), QLineEdit::Normal,
                                                "", &ok);
    if (!ok || productName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Имя продукта не введено.");
        return;
    }
    
    int qty = QInputDialog::getInt(this, tr("Количество"), tr("Введите количество:"), 1, 1, 1000, 1, &ok);
    if (!ok || qty <= 0) {
        QMessageBox::warning(this, "Ошибка", "Некорректное количество.");
        return;
    }
    
    double discount = QInputDialog::getDouble(this, tr("Скидка"), tr("Введите скидку (%):"), 0, 0, 100, 1, &ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Скидка не введена.");
        return;
    }

    QString sellerName = QInputDialog::getText(this, tr("Продажа от лица продавца"),
                                               tr("Имя продавца:"), QLineEdit::Normal,
                                               "", &ok);
    if (!ok || sellerName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Имя продавца не введено.");
        return;
    }

    vapeShop->makeSale(productName.toStdString(), qty, discount, sellerName.toStdString());
    QMessageBox::information(this, "Продажа", QString("Продажа завершена: %1 x %2 со скидкой %3% от продавца %4.")
                                            .arg(productName).arg(qty).arg(discount).arg(sellerName));
}

void MainWindow::displaySalesHistory() {
    QString info = "История продаж:\n";

    auto salesHistory = vapeShop->getSalesHistory();
    for (const auto& sale : salesHistory) {
        info += QString("Продукт: %1, Количество: %2, Цена продажи: %3, Скидка: %4, Прибыль: %5\n")
                   .arg(QString::fromStdString(sale.getProductName()))
                   .arg(sale.getQuantitySold())
                   .arg(sale.getSalePrice())
                   .arg(sale.getDiscount())
                   .arg(sale.getProfit());
    }

    infoDisplay->setText(info);
}
