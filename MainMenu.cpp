#include "MainMenu.hpp"
#include <raylib.h>

void MainMenu::draw() {
    BeginDrawing();
    ClearBackground(WHITE);
    ui.text(0, "Hitlog", {473, 243, 536, 268}, 250);
    if (ui.button(1, "Start Game", {611, 565, 258, 58}, 48)) {
        Globals::sceneManager->switchScene(1);
    }
    ui.button(2, "Settings", {646, 664, 188, 58}, 48);
    EndDrawing();
}

void MainMenu::enter() {
}

void MainMenu::update(float delta) {
}

void MainMenu::exit() {
}