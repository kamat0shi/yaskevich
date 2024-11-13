#pragma once
#include <iterator>
#include <vector>
#include <memory>

template <typename T>
class ContainerIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

private:
    typename std::vector<std::unique_ptr<T>>::iterator it;

public:
    explicit ContainerIterator(typename std::vector<std::unique_ptr<T>>::iterator init) : it(init) {}

    reference operator*() const { return **it; }
    pointer operator->() const { return it->get(); }

    ContainerIterator& operator++() {
        ++it;
        return *this;
    }

    ContainerIterator operator++(int) {
        ContainerIterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const ContainerIterator& other) const { return it == other.it; }
    bool operator!=(const ContainerIterator& other) const { return it != other.it; }
};