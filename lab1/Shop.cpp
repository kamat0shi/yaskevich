#include "Shop.hpp"

Shop::Shop(const std::string_view n) : name(n) {}

void Shop::addSeller(std::unique_ptr<Seller> seller) {
    sellers.push_back(std::move(seller));
}

void Shop::removeSeller(const std::string_view sellerName) {
    auto it = std::ranges::remove_if(sellers, [&](const auto& seller) {
        return seller->getName() == sellerName;
    });
    sellers.erase(it.begin(), it.end());
    if (it.begin() != sellers.end()) {
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
    auto it = std::ranges::remove_if(products, [&](const auto& product) {
        return product->getName() == productName;
    });
    products.erase(it.begin(), it.end());
    if (it.begin() != products.end()) {
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
