#include "MainMenu.hpp"
#include <raylib.h>

void MainMenu::draw() {
    BeginDrawing();
    ClearBackground(WHITE);
    ui.text(0, "Hitlog", {323, 143, 536, 268}, 250);
    if (ui.button(1, "Start Game", {471, 565, 258, 58}, 48)) {
        Globals::sceneManager->switchScene(1);
    }
    ui.button(2, "Settings", {506, 664, 188, 58}, 48);
    EndDrawing();
}

void MainMenu::enter() {
    bgMusic = LoadSound("./assets/music/music_main_menu.wav");
    PlaySound(bgMusic);
}

void MainMenu::update(float delta) {
    if (!IsSoundPlaying(bgMusic)) {
        PlaySound(bgMusic);
    }
}

void MainMenu::exit() {
    UnloadSound(bgMusic);
}