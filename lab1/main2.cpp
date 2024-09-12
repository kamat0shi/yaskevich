#include <iostream>
#include <vector>
#include <string>

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
protected:
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
    vector<Seller*> sellers;
    vector<Product*> products;

public:
    Shop(const std::string_view n) : name(n) {}

    void addSeller(Seller* seller) {
        sellers.push_back(seller);
    }

    void removeSeller(const std::string_view sellerName) {
        for (auto it = sellers.begin(); it != sellers.end(); ++it) {
            if ((*it)->getName() == sellerName) {
                delete *it;
                sellers.erase(it);
                cout << "Продавец " << sellerName << " удален." << endl;
                return;
            }
        }
        cout << "Продавец не найден." << endl;
    }

    Seller* getSeller(const std::string_view sellerName) {
        for (Seller* seller : sellers) {
            if (seller->getName() == sellerName) {
                return seller;
            }
        }
        return nullptr;
    }

    void addProduct(Product* product) {
        products.push_back(product);
    }

    void removeProduct(const std::string_view productName) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if ((*it)->getName() == productName) {
                delete *it;
                products.erase(it);
                cout << "Товар " << productName << " удален." << endl;
                return;
            }
        }
        cout << "Товар не найден." << endl;
    }

    Product* getProduct(const std::string_view productName) {
        for (Product* product : products) {
            if (product->getName() == productName) {
                return product;
            }
        }
        return nullptr;
    }

    void displayShop(bool isAdmin) const {
        cout << "Магазин: " << name << endl;
        cout << "Продавцы:" << endl;
        for (Seller* seller : sellers) {
            seller->displaySeller();
        }
        cout << "Товары:" << endl;
        for (Product* product : products) {
            product->displayProduct(isAdmin);
        }
    }

    ~Shop() {
        for (Seller* seller : sellers) {
            delete seller; 
        }
        for (Product* product : products) {
            delete product;
        }
    }
};

int main() {
    Shop* vapeShop = new Shop("Scam Judas");

    Seller* seller1 = new Seller("Даник", 800);
    Seller* seller2 = new Seller("Яна", 1000, true);
    vapeShop->addSeller(seller1);
    vapeShop->addSeller(seller2);

    Product* product1 = new Product("Xros 3 mini", 85, 54, 3);
    Product* product2 = new Product("Hotspot", 15, 8, 60);
    vapeShop->addProduct(product1);
    vapeShop->addProduct(product2);

    cout << "Информация для обычного продавца (Даник):" << endl;
    vapeShop->displayShop(seller1->getIsAdmin());

    cout << "\nИнформация для администратора (Яна):" << endl;
    vapeShop->displayShop(seller2->getIsAdmin());

    vapeShop->removeSeller("Даник");

    vapeShop->removeProduct("Hotspot");

    vapeShop->displayShop(seller2->getIsAdmin());

    delete vapeShop;

    return 0;
}
