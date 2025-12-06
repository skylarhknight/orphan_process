#include "Terminal.h"
#include <iostream>
#include <cstdlib>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

Terminal::Terminal() {
    // hideCursor();
}

void Terminal::clear() {
#ifdef _WIN32
    std::system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

void Terminal::setGreen() {
    std::cout << "\033[1;32m";
}

void Terminal::resetColor() {
    std::cout << "\033[0m";
}

void Terminal::hideCursor() {
    std::cout << "\033[?25l";
}

// Moves the cursor to specific coordinates (ANSI Escape Codes)
void Terminal::moveCursor(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

void Terminal::print(const std::string& message) {
    std::cout << message << std::endl;
}

void Terminal::drawText(int x, int y, std::string text) {
    moveCursor(y, x);
    std::cout << text;
}

void Terminal::drawCentered(int y, std::string text) {
    // Assuming standard 80 width
    int x = (80 - text.length()) / 2;
    if (x < 1) x = 1;
    moveCursor(y, x);
    std::cout << text;
}

void Terminal::drawBox(int x, int y, int width, int height, std::string title) {
    // 1. Draw Top Border
    moveCursor(y, x);
    std::cout << "+";
    for (int i = 0; i < width - 2; i++) std::cout << "-";
    std::cout << "+";

    // 2. Draw Title if exists
    if (!title.empty()) {
        moveCursor(y, x + 2);
        std::cout << "[ " << title << " ]";
    }

    // 3. Draw Sides
    for (int i = 1; i < height - 1; i++) {
        moveCursor(y + i, x);
        std::cout << "|";
        moveCursor(y + i, x + width - 1);
        std::cout << "|";
    }

    // 4. Draw Bottom Border
    moveCursor(y + height - 1, x);
    std::cout << "+";
    for (int i = 0; i < width - 2; i++) std::cout << "-";
    std::cout << "+";
}