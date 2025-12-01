#pragma once
#include <raylib.h>
#include <string>

struct UILibrary {
    int hot = -1;
    int active = -1;
    
    Font font;

    UILibrary();
    ~UILibrary();
    void text(int id, const std::string& text, const Rectangle& bounds, float fontSize);
    bool button(int id, const std::string& text, const Rectangle& bounds, float fontSize);
};