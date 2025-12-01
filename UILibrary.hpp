#pragma once
#include "raylib.h"
#include "raymath.h"
#include <string>
#include <functional>
#include <vector>

struct UILibrary {
    int hot = -1;
    int active = -1;
    
    Font font;

    UILibrary();
    ~UILibrary();
    void text(int id, const std::string& text, const Rectangle& bounds, float fontSize, Color textColor);
    bool button(int id, const std::string& text, const Rectangle& bounds, float fontSize);
    int progressBar(int id, const Rectangle& bounds, int progressCurrentValue, int progressMaxValue, Color progressColor);
};