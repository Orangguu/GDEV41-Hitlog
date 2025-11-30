#include "UILibrary.hpp"

#include <raylib.h>
#include <raymath.h>

#include <functional>
#include <iostream>
#include <string>
#include <vector>

UILibrary::UILibrary() {
    font = LoadFontEx("assets/fonts/jersey10.ttf", 256, 0, 0);
}

UILibrary::~UILibrary() {
    UnloadFont(font);
}

void UILibrary::text(int id, const std::string& text, const Rectangle& bounds, float fontSize) {
    if (id == active) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (id == hot) {
            }

            active = -1;
        }
    }

    if (id == hot) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            active = id;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), bounds)) {
        hot = id;
    }
    else if (hot == id) {
        hot = -1;
    }

    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, 0);
    DrawTextEx(font, text.c_str(), (Vector2){(bounds.x + ((bounds.width - textSize.x) / 2)), (bounds.y + ((bounds.height - textSize.y) / 2))}, fontSize, 0, BLACK);
}

bool UILibrary::button(int id, const std::string& text, const Rectangle& bounds, float fontSize) {
    Color bgColor = GRAY;
    Color textColor = BLACK;
    bool result = false;

    if (id == active) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (id == hot) {
                result = true;
            }

            active = -1;
        }
    }

    if (id == hot) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            active = id;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), bounds)) {
        hot = id;
    }
    else if (hot == id) {
        hot = -1;
    }

    if (active == id) {
        bgColor = BLACK;
        textColor = WHITE;
    }
    else if (hot == id) {
        bgColor = DARKGRAY;
        textColor = BLACK;
    }
    else {
        bgColor = GRAY;
        textColor = BLACK;
    }

    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, 0);

    DrawRectangleRec(bounds, bgColor);
    DrawTextEx(font, text.c_str(), (Vector2){(bounds.x + ((bounds.width - textSize.x) / 2)), (bounds.y + ((bounds.height - textSize.y) / 2))}, fontSize, 0, textColor);

    return result;
}