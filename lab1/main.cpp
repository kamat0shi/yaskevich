#include <iostream>
#include <memory>
#include "Shop.hpp"

using namespace std;

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
