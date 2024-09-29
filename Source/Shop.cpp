#include "Shop.hpp"
#include "Sale.hpp"

Shop::Shop(const std::string_view n) : name(n) {}

void Shop::addSeller(std::unique_ptr<Seller> seller) {
    sellers.push_back(std::move(seller));
}

void Shop::removeSeller(const std::string_view sellerName) {
    size_t initialSize = sellers.size();
    auto it = std::ranges::remove_if(sellers, [&](const auto& seller) {
        return seller->getName() == sellerName;
    });
    sellers.erase(it.begin(), it.end());
    if (sellers.size() < initialSize) {
        std::cout << "Продавец " << sellerName << " удален." << std::endl;
    } else {
        std::cout << "Продавец не найден." << std::endl;
    }
}

Seller* Shop::getSeller(const std::string_view sellerName) {
    for (const auto& seller : sellers) {
        if (seller->getName() == sellerName) {
            return seller.get();
        }
    }
    return nullptr;
}

void Shop::addProduct(std::unique_ptr<Product> product) {
    products.push_back(std::move(product));
}

void Shop::removeProduct(const std::string_view productName) {
    size_t initialSize = products.size();
    auto it = std::ranges::remove_if(products, [&](const auto& product) {
        return product->getName() == productName;
    });
    products.erase(it.begin(), it.end());
    if (products.size() < initialSize) {
        std::cout << "Товар " << productName << " удален." << std::endl;
    } else {
        std::cout << "Товар не найден." << std::endl;
    }
}

Product* Shop::getProduct(const std::string_view productName) {
    for (const auto& product : products) {
        if (product->getName() == productName) {
            return product.get();
        }
    }
    return nullptr;
}

void Shop::displayShop(bool isAdmin) const {
    std::cout << "Магазин: " << name << std::endl;
    std::cout << "Продавцы:" << std::endl;
    for (const auto& seller : sellers) {
        seller->displaySeller();
    }
    std::cout << "Товары:" << std::endl;
    for (const auto& product : products) {
        product->displayProduct(isAdmin);
    }
}

void Shop::makeSale(const std::string_view productName, int qty, double discount) {
    Product* product = getProduct(productName);
    if (product && product->getQuantity() >= qty) {
        double retailPrice = product->getRetailPrice();
        double wholesalePrice = product->getWholesalePrice(true); 
        double salePrice = retailPrice * qty * (1 - discount / 100.0);
        double profit = (salePrice - wholesalePrice * qty);

        product->reduceQuantity(qty);

        salesHistory.emplace_back(productName, qty, salePrice, discount, profit);

        std::cout << "Продажа завершена! Прибыль: $" << profit << std::endl;
    } else {
        std::cout << "Товар не найден или недостаточно количества!" << std::endl;
    }
}

void Shop::displaySalesHistory() const {
    std::cout << "История продаж: " << std::endl;
    for (const auto& sale : salesHistory) {
        sale.displaySale();
    }
}
