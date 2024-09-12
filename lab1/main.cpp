#include <iostream>
#include "shop.h"
#include "seller.h"
#include "product.h"
#include <memory>

using namespace std;

int main() {
    auto vapeShop = std::make_unique<Shop>("Scam_Judas");

    auto seller1 = std::make_unique<Seller>("Данила", 800);
    auto seller2 = std::make_unique<Seller>("Яна", 1000, true);
    vapeShop->addSeller(seller1.get());
    vapeShop->addSeller(seller2.get());

    auto product1 = std::make_unique<Product>("Xros 3 mini", 85, 54, 3);
    auto product2 = std::make_unique<Product>("Hotspot", 15, 8, 60);
    vapeShop->addProduct(product1.get());
    vapeShop->addProduct(product2.get());

    cout << "Информация для обычного продавца (Данила):" << endl;
    vapeShop->displayShop(seller1->getIsAdmin());

    cout << "\nИнформация для администратора (Яна):" << endl;
    vapeShop->displayShop(seller2->getIsAdmin());

    vapeShop->removeSeller("Данила");

    vapeShop->removeProduct("Hotspot");

    vapeShop->displayShop(seller2->getIsAdmin());

    return 0;
}