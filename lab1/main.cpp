#include <iostream>
#include "shop.h"
#include "seller.h"
#include "product.h"

using namespace std;

int main() {
    Shop* vapeShop = new Shop("Scam_Judas");

    Seller* seller1 = new Seller("Данила", 800);
    Seller* seller2 = new Seller("Яна", 1000, true);
    vapeShop->addSeller(seller1);
    vapeShop->addSeller(seller2);

    Product* product1 = new Product("Xros 3 mini", 85, 54, 3);
    Product* product2 = new Product("Hotspot", 15, 8, 60);
    vapeShop->addProduct(product1);
    vapeShop->addProduct(product2);

    cout << "Информация для обычного продавца (Данила):" << endl;
    vapeShop->displayShop(seller1->getIsAdmin());

    cout << "\nИнформация для администратора (Яна):" << endl;
    vapeShop->displayShop(seller2->getIsAdmin());

    vapeShop->removeSeller("Данила");

    vapeShop->removeProduct("Hotspot");

    vapeShop->displayShop(seller2->getIsAdmin());

    delete vapeShop;

    return 0;
}