#ifndef SYSTEMLOG_H
#define SYSTEMLOG_H

#include <string>
#include "../lib_terminal/Terminal.h" // We need this to print to our screen

// A single entry in the log
struct LogNode {
    std::string message;
    LogNode* next;
    
    LogNode(std::string msg) : message(msg), next(nullptr) {}
};

class SystemLog {
private:
    LogNode* head;
    LogNode* tail;
    int size;
    int maxLines; // Limit log to 5-10 lines so it fits on screen

public:
    SystemLog();
    ~SystemLog(); // Destructor is CRITICAL for memory management points

    void addEntry(std::string message);
    void printLog(Terminal& term); // Pass our terminal object to render it
};

#endif