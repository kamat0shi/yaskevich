#include <iostream>
#include <memory>
#include "Shop.hpp"

using namespace std;

void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Display shop information (non-admin)" << endl;
    cout << "2. Display shop information (admin)" << endl;
    cout << "3. Remove seller" << endl;
    cout << "4. Remove product" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    auto vapeShop = make_unique<Shop>("Scam Judas");

    auto seller1 = make_unique<Seller>("Danik", 800);
    auto seller2 = make_unique<Seller>("Яна", 1000, true);
    vapeShop->addSeller(std::move(seller1));
    vapeShop->addSeller(std::move(seller2));

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
            case 5:
                running = false;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
        if (running) {
            cout << "\nPress Enter to return to the menu...";
            cin.get();
        }
    }

    return 0;
}

