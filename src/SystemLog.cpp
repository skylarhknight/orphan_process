#include "../include/SystemLog.h"

SystemLog::SystemLog() : head(nullptr), tail(nullptr), size(0), maxLines(8) {}

SystemLog::~SystemLog() {
    // Traverse the list and delete every node to prevent memory leaks
    LogNode* current = head;
    while (current != nullptr) {
        LogNode* next = current->next;
        delete current;
        current = next;
    }
}

void SystemLog::addEntry(std::string message) {
    LogNode* newNode = new LogNode(message);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        // Add to the END of the list
        tail->next = newNode;
        tail = newNode;
    }
    size++;

    // If we exceed maxLines, remove the OLDEST entry (head)
    if (size > maxLines) {
        LogNode* temp = head;
        head = head->next;
        delete temp;
        size--;
    }
}

void SystemLog::printLog(Terminal& term) {
    term.print("--- SYSTEM LOG ---");
    LogNode* current = head;
    while (current != nullptr) {
        term.print("> " + current->message);
        current = current->next;
    }
}