#include "MainMenu.hpp"
#include "UILibrary.hpp"
#include <raylib.h>

MainMenu::MainMenu(int windowWidth, int windowHeight) {
    WINDOW_WIDTH = windowWidth;
    WINDOW_HEIGHT = windowHeight;
}

void MainMenu::update(float delta) {
    ClearBackground(WHITE);
    ui.text(0, "Hitlog", {323, 143, 536, 268}, 250);
    ui.button(1, "Start Game", {471, 565, 258, 58}, 48);
    ui.button(2, "Settings", {506, 664, 188, 58}, 48);
}