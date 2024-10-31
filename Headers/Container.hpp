#pragma once
#include "../Headers/Product.hpp"
#include "../Headers/Seller.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

template <typename T>
class Container {
private:
    std::vector<std::unique_ptr<T>> items;

public:
    void addItem(std::unique_ptr<T> item) {
        items.push_back(std::move(item));
    }

    void removeItem(const std::string& name) {
        auto it = std::remove_if(items.begin(), items.end(), [&name](const std::unique_ptr<T>& item) {
            return item->getName() == name;
        });
        if (it != items.end()) {
            items.erase(it, items.end());
        }
    }

    T* findItem(const std::string& name) const {
        for (const auto& item : items) {
            if (item->getName() == name) {
                return item.get();
            }
        }
        return nullptr;
    }

    void displayAll(bool isAdmin = false) const {
        for (const auto& item : items) {
            if constexpr (std::is_same_v<T, Product>) {
                item->displayInfo(isAdmin);
            } else {
                item->displayInfo();
            }
        }
    }

    const std::vector<std::unique_ptr<T>>& getItems() const {
        return items;
    }
};