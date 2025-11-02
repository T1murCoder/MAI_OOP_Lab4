#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

template <class T>
class Array {
public:
    Array(): data(nullptr), capacity(0), current_size(0) {}
    explicit Array(const size_t size): current_size(0), capacity(size) {
        if (size > 0) {
            data = std::make_shared<T[]>(size);
        } else {
            data = nullptr;
        }
    }
    ~Array() = default;

    void add(const T& value) {
        ensure_capacity_for_one();
        data[current_size++] = value;
    }

    void pop_back() {
        if (current_size > 0) --current_size;
    }

    void remove(const size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }

        T removed = std::move(data[index]);

        for (size_t i = index; i < current_size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }

        --current_size;
    }

    void clear() noexcept {
        data.reset();
        current_size = 0;
        capacity = 0;
    };

    bool empty() const {
        return current_size == 0;
    };

    size_t size() const {
        return current_size;
    }
    size_t cap() const {
        return capacity;
    }

    const T& operator[](const size_t index) const {
        if (index >= current_size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    T& operator[](const size_t index) {
        if (index >= current_size) throw std::out_of_range("Index out of range");
        return data[index];
    }
private:
    std::shared_ptr<T[]> data;
    size_t current_size;
    size_t capacity;

    void ensure_capacity_for_one() {
        if (capacity == 0) {
            resize_capacity(4);
            return;
        }
        if (current_size >= capacity) {
            resize_capacity(capacity * 2);
        }
    }


    void resize_capacity(const size_t new_capacity) {
        if (new_capacity == capacity) return;
        std::shared_ptr<T[]> new_data = std::make_shared<T[]>(new_capacity);
        for (size_t i = 0; i < current_size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        data = std::move(new_data);
        capacity = new_capacity;
    }
};
