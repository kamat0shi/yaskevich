#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <sstream>
#include <optional>
#include <memory>
#include <type_traits>

template <typename Container, typename Getter>
std::optional<std::string> printInfoByName(const Container& container, const std::string& name, Getter getName, bool isAdmin = false) {
    std::stringstream ss;
    for (const auto& item : container) {
        if (getName(*item) == name) {
            if constexpr (std::is_same_v<typename Container::value_type::element_type, Product>) {
                ss << "Название: " << item->getName() << ", Розничная цена: " << item->getRetailPrice();
                if (isAdmin) {
                    ss << ", Оптовая цена: " << item->getWholesalePrice(isAdmin);
                }
                ss << ", Количество: " << item->getQuantity() << "\n";
            } else {
                ss << *item << "\n";
            }
            return ss.str();
        }
    }
    return std::nullopt;
}

#endif