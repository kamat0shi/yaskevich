#ifndef REPORTWINDOW_HPP
#define REPORTWINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <sqlite3.h>

class ReportWindow : public QWidget {
    Q_OBJECT

public:
    explicit ReportWindow(QWidget *parent = nullptr);
    ~ReportWindow() override;

private slots:
    void fetchShopId();
    void downloadSalesHistory();
    void downloadProductList();
    void downloadSellerList();

private:
    QLineEdit *shopNameInput;
    QLineEdit *roleFilter;
    QLineEdit *minQuantityFilter;
    sqlite3* db;
    int shop_id = 0;
};

#endif