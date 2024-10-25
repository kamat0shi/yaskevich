#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTextEdit>
#include <sqlite3.h>
#include "../Headers/Shop.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

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
    QTextEdit* infoDisplay;  // Обычный указатель на QTextEdit
    Shop* vapeShop;  // Обычный указатель на Shop
    sqlite3* db;  
};

#endif