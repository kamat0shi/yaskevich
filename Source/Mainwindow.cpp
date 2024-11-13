#include "../Headers/Mainwindow.hpp"
#include "../Headers/Utility.hpp" 
#include "../Headers/CustomException.hpp"
#include "../Headers/ReportWindow.hpp"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QTextEdit>
#include <QInputDialog>
#include <QLineEdit>
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <memory>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    if (int rc = sqlite3_open("../shop_db.db", &db); rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    vapeShop = std::make_unique<Shop>("Scam_Judas", db);

    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);

    auto *label = new QLabel("Меню магазина", this);
    layout->addWidget(label);

    auto *button1 = new QPushButton("Отобразить информацию о магазине (не админ)", this);
    auto *button2 = new QPushButton("Отобразить информацию о магазине (админ)", this);
    auto *button3 = new QPushButton("Удалить продавца", this);
    auto *button4 = new QPushButton("Удалить продукт", this);
    auto *button5 = new QPushButton("Совершить продажу", this);
    auto *button6 = new QPushButton("Добавить продавца", this);  
    auto *button7 = new QPushButton("Добавить продукт", this);   
    auto *button8 = new QPushButton("История продаж", this);
    auto *button9 = new QPushButton("Найти информацию по имени", this);
    auto *reportButton = new QPushButton("Загрузить отчеты", this);


    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);
    layout->addWidget(button5);
    layout->addWidget(button6);
    layout->addWidget(button7);
    layout->addWidget(button8);
    layout->addWidget(button9);
    layout->addWidget(reportButton);


    infoDisplay = new QTextEdit(this);
    infoDisplay->setReadOnly(true);
    layout->addWidget(infoDisplay);

    setCentralWidget(centralWidget);

    connect(button1, &QPushButton::clicked, this, &MainWindow::displayShopNonAdmin);
    connect(button2, &QPushButton::clicked, this, &MainWindow::displayShopAdmin);
    connect(button3, &QPushButton::clicked, this, &MainWindow::removeSeller);
    connect(button4, &QPushButton::clicked, this, &MainWindow::removeProduct);
    connect(button5, &QPushButton::clicked, this, &MainWindow::makeSale);
    connect(button6, &QPushButton::clicked, this, &MainWindow::addSeller);  
    connect(button7, &QPushButton::clicked, this, &MainWindow::addProduct);
    connect(button8, &QPushButton::clicked, this, &MainWindow::displaySalesHistory);
    connect(button9, &QPushButton::clicked, this, &MainWindow::displayInfoByName);
    connect(reportButton, &QPushButton::clicked, this, [this]() { // Захват “this” позволяет лямбда-функции использовать указатель на объект MainWindow для вызова методов и управления жизненным циклом дочерних окон, таких как ReportWindow.
        ReportWindow *reportWindow = new ReportWindow();
        reportWindow->setAttribute(Qt::WA_DeleteOnClose);
        reportWindow->show();
    });
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
    try {
        bool ok;
        QString name = QInputDialog::getText(this, tr("Добавить продавца"),
                                             tr("Имя продавца:"), QLineEdit::Normal,
                                             "", &ok);
        if (!ok || name.isEmpty()) {
            throw CustomException("Имя продавца не введено.");
        }

        double salary = QInputDialog::getDouble(this, tr("Зарплата"), tr("Введите зарплату:"), 0, 0, 10000, 2, &ok);
        if (!ok || salary <= 0) {
            throw CustomException("Некорректная зарплата.");
        }

        bool isAdmin = QInputDialog::getInt(this, tr("Администратор?"), tr("Введите 1, если администратор, 0 если нет:"), 0, 0, 1, 1, &ok);
        if (!ok) {
            throw CustomException("Ошибка при вводе данных о роли администратора.");
        }

        vapeShop->addSeller(std::make_unique<Seller>(name.toStdString(), salary, isAdmin));
        QMessageBox::information(this, "Добавление", "Продавец успешно добавлен.");

    } catch (const CustomException& e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    } catch (const std::runtime_error& e) {  
        QMessageBox::critical(this, "Ошибка", QString("Runtime error: %1").arg(e.what()));
    }
}

void MainWindow::removeSeller() {
    try {
        bool ok;
        QString sellerName = QInputDialog::getText(this, tr("Удалить продавца"),
                                                   tr("Имя продавца:"), QLineEdit::Normal,
                                                   "", &ok);
        if (!ok || sellerName.isEmpty()) {
            throw CustomException("Имя продавца не введено.");
        }

        vapeShop->removeSeller(sellerName.toStdString()); 
        QMessageBox::information(this, "Удаление", QString("Продавец %1 удален.").arg(sellerName));

    } catch (const CustomException& e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    } catch (const std::runtime_error& e) {  
        QMessageBox::critical(this, "Ошибка", QString("Runtime error: %1").arg(e.what()));
    }
}

void MainWindow::addProduct() {
    try {
        bool ok;
        QString name = QInputDialog::getText(this, tr("Добавить продукт"),
                                             tr("Имя продукта:"), QLineEdit::Normal,
                                             "", &ok);
        if (!ok || name.isEmpty()) {
            throw CustomException("Имя продукта не введено.");
        }

        double retailPrice = QInputDialog::getDouble(this, tr("Розничная цена"), tr("Введите розничную цену:"), 0, 0, 10000, 2, &ok);
        if (!ok || retailPrice <= 0) {
            throw CustomException("Некорректная розничная цена.");
        }

        double wholesalePrice = QInputDialog::getDouble(this, tr("Оптовая цена"), tr("Введите оптовую цену:"), 0, 0, 10000, 2, &ok);
        if (!ok || wholesalePrice <= 0) {
            throw CustomException("Некорректная оптовая цена.");
        }

        int quantity = QInputDialog::getInt(this, tr("Количество"), tr("Введите количество товара:"), 1, 1, 1000, 1, &ok);
        if (!ok || quantity <= 0) {
            throw CustomException("Некорректное количество.");
        }

        vapeShop->addProduct(std::make_unique<Product>(name.toStdString(), retailPrice, wholesalePrice, quantity));
        QMessageBox::information(this, "Добавление", "Продукт успешно добавлен.");

    } catch (const CustomException& e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    } catch (const std::runtime_error& e) {  
        QMessageBox::critical(this, "Ошибка", QString("Runtime error: %1").arg(e.what()));
    }
}

void MainWindow::removeProduct() {
    try {
        bool ok;
        QString productName = QInputDialog::getText(this, tr("Удалить продукт"),
                                                    tr("Имя продукта:"), QLineEdit::Normal,
                                                    "", &ok);
        if (!ok || productName.isEmpty()) {
            throw CustomException("Имя продукта не введено.");
        }

        vapeShop->removeProduct(productName.toStdString()); 
        QMessageBox::information(this, "Удаление", QString("Продукт %1 удален.").arg(productName));

    } catch (const CustomException& e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    } catch (const std::runtime_error& e) {  
        QMessageBox::critical(this, "Ошибка", QString("Runtime error: %1").arg(e.what()));
    }
}

void MainWindow::makeSale() {
    try {
        bool ok;

        QString productName = QInputDialog::getText(this, tr("Продажа товара"),
                                                    tr("Имя продукта:"), QLineEdit::Normal,
                                                    "", &ok);
        if (!ok || productName.isEmpty()) {
            throw CustomException("Имя продукта не введено.");
        }

        int qty = QInputDialog::getInt(this, tr("Количество"), tr("Введите количество:"), 1, 1, 1000, 1, &ok);
        if (!ok || qty <= 0) {
            throw CustomException("Некорректное количество.");
        }

        double discount = QInputDialog::getDouble(this, tr("Скидка"), tr("Введите скидку (%):"), 0, 0, 100, 1, &ok);
        if (!ok) {
            throw CustomException("Скидка не введена.");
        }

        QString sellerName = QInputDialog::getText(this, tr("Продажа от лица продавца"),
                                                   tr("Имя продавца:"), QLineEdit::Normal,
                                                   "", &ok);
        if (!ok || sellerName.isEmpty()) {
            throw CustomException("Имя продавца не введено.");
        }

        vapeShop->makeSale(productName.toStdString(), qty, discount, sellerName.toStdString());
        QMessageBox::information(this, "Продажа", QString("Продажа завершена: %1 x %2 со скидкой %3% от продавца %4.")
                                                .arg(productName).arg(qty).arg(discount).arg(sellerName));

    } catch (const CustomException& e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    } catch (const std::runtime_error& e) {  
        QMessageBox::critical(this, "Ошибка", QString("Runtime error: %1").arg(e.what()));
    }
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

void MainWindow::displayInfoByName() {
    bool ok;
    QString name = QInputDialog::getText(this, tr("Введите имя"),
                                         tr("Введите имя продукта или продавца:"), 
                                         QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    bool isAdmin = true; 

    QString info;

    if (auto productInfo = printInfoByName(vapeShop->getProducts(), name.toStdString(), [](const Product& p) {
        return p.getName();
    }, isAdmin)) {
        info += QString::fromStdString(*productInfo);
    } else if (auto sellerInfo = printInfoByName(vapeShop->getSellers(), name.toStdString(), [](const Seller& s) {
        return s.getName();
    })) {
        info += QString::fromStdString(*sellerInfo);
    } else {
        info += QString("Элемент с именем \"%1\" не найден.\n").arg(name);
    }

    infoDisplay->setText(info);
}