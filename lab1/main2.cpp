#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;

class Product {
private:
    string name;
    double retailPrice;
    double wholesalePrice;
    int quantity;

public:
    Product(const std::string_view n, double rPrice, double wPrice, int q)
        : name(n), retailPrice(rPrice), wholesalePrice(wPrice), quantity(q) {}

    void setName(const std::string_view n) { name = n; }
    void setRetailPrice(double rPrice) { retailPrice = rPrice; }
    void setWholesalePrice(double wPrice) { wholesalePrice = wPrice; }
    void setQuantity(int q) { quantity = q; }

    string getName() const { return name; }
    double getRetailPrice() const { return retailPrice; }
    double getWholesalePrice(bool isAdmin) const {
        if (isAdmin) {
            return wholesalePrice;
        } else {
            cout << "Доступ запрещен: только администратор может просматривать оптовую цену!" << endl;
            return -1;
        }
    }
    int getQuantity() const { return quantity; }

    void displayProduct(bool isAdmin) const {
        cout << "Название: " << name << ", Розничная цена: " << retailPrice << ", Количество: " << quantity << endl;
        if (isAdmin) {
            cout << "Оптовая цена: " << wholesalePrice << endl;
        }
    }
};

class Seller {
private:
    string name;
    double salary;
    bool isAdmin;

public:
    Seller(const std::string_view n, double s, bool admin = false) : name(n), salary(s), isAdmin(admin) {}

    void setName(const std::string_view n) { name = n; }
    void setSalary(double s) { salary = s; }

    string getName() const { return name; }
    double getSalary() const { return salary; }
    bool getIsAdmin() const { return isAdmin; }

    void displaySeller() const {
        cout << "Имя: " << name << ", Зарплата: " << salary;
        if (isAdmin) {
            cout << " (Администратор)";
        }
        cout << endl;
    }
};

class Shop {
private:
    string name;
    vector<unique_ptr<Seller>> sellers;
    vector<unique_ptr<Product>> products;

public:
    explicit Shop(const std::string_view n) : name(n) {}

    void addSeller(unique_ptr<Seller> seller) {
        sellers.push_back(std::move(seller));
    }

    void removeSeller(const std::string_view sellerName) {
        auto it = std::remove_if(sellers.begin(), sellers.end(), [&](const unique_ptr<Seller>& seller) {
            return seller->getName() == sellerName;
        });
        if (it != sellers.end()) {
            sellers.erase(it, sellers.end());
            cout << "Продавец " << sellerName << " удален." << endl;
        } else {
            cout << "Продавец не найден." << endl;
        }
    }

    Seller* getSeller(const std::string_view sellerName) {
        for (auto& seller : sellers) {
            if (seller->getName() == sellerName) {
                return seller.get();
            }
        }
        return nullptr;
    }

    void addProduct(unique_ptr<Product> product) {
        products.push_back(std::move(product));
    }

    void removeProduct(const std::string_view productName) {
        auto it = std::remove_if(products.begin(), products.end(), [&](const unique_ptr<Product>& product) {
            return product->getName() == productName;
        });
        if (it != products.end()) {
            products.erase(it, products.end());
            cout << "Товар " << productName << " удален." << endl;
        } else {
            cout << "Товар не найден." << endl;
        }
    }

    Product* getProduct(const std::string_view productName) {
        for (auto& product : products) {
            if (product->getName() == productName) {
                return product.get();
            }
        }
        return nullptr;
    }

    void displayShop(bool isAdmin) const {
        cout << "Магазин: " << name << endl;
        cout << "Продавцы:" << endl;
        for (const auto& seller : sellers) {
            seller->displaySeller();
        }
        cout << "Товары:" << endl;
        for (const auto& product : products) {
            product->displayProduct(isAdmin);
        }
    }
};

int main() {
    auto vapeShop = std::make_unique<Shop>("Scam Judas");

    auto seller1 = std::make_unique<Seller>("Даник", 800);
    auto seller2 = std::make_unique<Seller>("Яна", 1000, true);
    vapeShop->addSeller(std::move(seller1));
    vapeShop->addSeller(std::move(seller2));

    auto product1 = std::make_unique<Product>("Xros 3 mini", 85, 54, 3);
    auto product2 = std::make_unique<Product>("Hotspot", 15, 8, 60);
    vapeShop->addProduct(std::move(product1));
    vapeShop->addProduct(std::move(product2));

    cout << "Информация для обычного продавца (Даник):" << endl;
    vapeShop->displayShop(false);

    cout << "\nИнформация для администратора (Яна):" << endl;
    vapeShop->displayShop(true);

    vapeShop->removeSeller("Даник");
    vapeShop->removeProduct("Hotspot");

    vapeShop->displayShop(true);

    return 0;
}
