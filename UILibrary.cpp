#include "UILibrary.hpp"

UILibrary::UILibrary() {
    font = LoadFontEx("assets/fonts/jersey10.ttf", 256, 0, 0);
}

UILibrary::~UILibrary() {
    UnloadFont(font);
}

void UILibrary::text(int id, const std::string& text, const Rectangle& bounds, float fontSize, Color textColor) {
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
    DrawTextEx(font, text.c_str(), (Vector2){(bounds.x + ((bounds.width - textSize.x) / 2)), (bounds.y + ((bounds.height - textSize.y) / 2))}, fontSize, 0, textColor);
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
        bgColor = { 190, 59, 9, 255 };
        textColor = WHITE;
    }
    else if (hot == id) {
        bgColor = { 156, 14, 62, 255 };
        textColor = WHITE;
    }
    else {
        bgColor = { 102, 32, 5, 255 };
        textColor = WHITE;
    }

    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, 0);

    DrawRectangleRec(bounds, bgColor);
    DrawTextEx(font, text.c_str(), (Vector2){(bounds.x + ((bounds.width - textSize.x) / 2)), (bounds.y + ((bounds.height - textSize.y) / 2))}, fontSize, 0, textColor);

    return result;
}

int UILibrary::progressBar(int id, const Rectangle& bounds, int progressCurrentValue, int progressMaxValue, Color progressColor) {
    float segmentSize = bounds.width / progressMaxValue;

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

    DrawRectangleRec(bounds, GRAY);
    DrawRectangleRec({bounds.x, bounds.y, (segmentSize * progressCurrentValue), bounds.height}, progressColor);

    return progressCurrentValue;
}

bool UILibrary::input(int id, InputField &field, float fontSize, Color textColor, Color bgColor) {
    Vector2 mousePos = GetMousePosition();

    // Hover detection
    if (CheckCollisionPointRec(mousePos, field.bounds)) {
        hot = id;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            active = id;
            field.isActive = true;
        }
    } else if (hot == id) {
        hot = -1;
    }

    // Deactivate if clicked outside
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !CheckCollisionPointRec(mousePos, field.bounds)) {
        if (active == id) {
            active = -1;
            field.isActive = false;
        }
    }

    // Handle keyboard input
    if (field.isActive) {
        int key = GetCharPressed();
        while (key > 0) {
            if (field.text.size() < field.maxLength) {
                field.text += (char)key;
            }
            key = GetCharPressed();
        }

        // Backspace
        if (IsKeyPressed(KEY_BACKSPACE) && !field.text.empty()) {
            field.text.pop_back();
        }
    }

    // Draw background
    DrawRectangleRec(field.bounds, bgColor);

    // Draw text (or placeholder if empty)
    std::string displayText = field.text.empty() ? field.placeholder : field.text;
    if (field.isActive && !field.text.empty()) displayText += "_"; // simple cursor

    Vector2 textSize = MeasureTextEx(font, displayText.c_str(), fontSize, 0);
    DrawTextEx(font, displayText.c_str(), {field.bounds.x + 5, field.bounds.y + (field.bounds.height - textSize.y) / 2}, fontSize, 0, textColor);

    return field.isActive;
}
