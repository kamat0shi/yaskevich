#pragma once
#include "../Headers/Product.hpp"
#include "../Headers/Seller.hpp"
#include "ContainerIterator.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <ranges>

template <typename T>
class Container {
private:
    std::vector<std::unique_ptr<T>> items;

public:
    using iterator = ContainerIterator<T>;

    void addItem(std::unique_ptr<T> item) {
        items.push_back(std::move(item));
    }

    void removeItem(const std::string& name) {
        auto it = std::ranges::remove_if(items, [&name](const std::unique_ptr<T>& item) {
            return item->getName() == name;
        });
        items.erase(it.begin(), it.end());
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

    iterator begin() { return iterator(items.begin()); }
    iterator end() { return iterator(items.end()); }
};