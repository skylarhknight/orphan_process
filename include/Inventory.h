#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include <iostream>
#include "../lib_terminal/Terminal.h"

// TEMPLATE CLASS (Requirement: Templates )
template <typename T>
class Inventory {
private:
    std::vector<T> items;
    int capacity;

public:
    Inventory(int cap = 5) : capacity(cap) {}

    // Add an item if there is space
    bool add(T item) {
        if (items.size() >= capacity) {
            return false; // Full
        }
        items.push_back(item);
        return true;
    }

    // Remove and return an item at a specific index
    T use(int index) {
        if (index < 0 || index >= items.size()) {
            throw std::out_of_range("Invalid Inventory Index");
        }
        T item = items[index];
        items.erase(items.begin() + index);
        return item;
    }

    bool isEmpty() const {
        return items.empty();
    }

    int size() const {
        return items.size();
    }

    // Print contents to the terminal
    void display(Terminal& term) {
        if (items.empty()) {
            term.print("   [EMPTY]");
            return;
        }
        for (int i = 0; i < items.size(); i++) {
            // This assumes T is a string or has an overload for string conversion
            term.print("   [" + std::to_string(i) + "] " + items[i]);
        }
    }
};

#endif