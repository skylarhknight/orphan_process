#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>

class Terminal {
public:
    Terminal();

    // Core Utilities
    void clear();
    void setGreen();
    void resetColor();
    void hideCursor();
    
    // Positioning 
    void moveCursor(int row, int col);

    // Drawing Helpers
    void print(const std::string& message);
    void drawBox(int x, int y, int width, int height, std::string title = "");
    void drawText(int x, int y, std::string text);
    void drawCentered(int y, std::string text);
};

#endif