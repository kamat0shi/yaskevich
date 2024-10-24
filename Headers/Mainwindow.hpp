#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTextEdit>
#include <sqlite3.h>
#include <memory>
#include "../Headers/Shop.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    exeplit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void displayShopNonAdmin();
    void displayShopAdmin();
    void removeSeller();
    void removeProduct();
    void makeSale();
    void addSeller();
    void addProduct();
    void displaySalesHistory();

private:
    QTextEdit *infoDisplay;  
    std::unique_ptr<Shop> vapeShop;
    sqlite3* db;  
};

#endif  