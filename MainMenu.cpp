#include "MainMenu.hpp"
#include "ResourceManager.hpp"
#include "raylib.h"

void MainMenu::draw() {
    BeginDrawing();
    
    if (bgTexture.id != 0) {
        DrawTexture(bgTexture, 0, 0, WHITE);
    }

    if (ui.button(1, "Start Game", {611, 565, 258, 58}, 48)) {
        Globals::sceneManager->switchScene(1);
    }
    ui.button(2, "Settings", {646, 664, 188, 58}, 48);
    EndDrawing();
}

void MainMenu::enter() {
    bgMusic = LoadSound("./assets/music/music_main_menu.wav");
    bgTexture = ResourceManager::getTexture("assets/backgrounds/title-screen.png");
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