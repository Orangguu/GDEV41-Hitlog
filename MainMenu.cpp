#include "MainMenu.hpp"
#include "ResourceManager.hpp"
#include "raylib.h"

void MainMenu::draw() {
    BeginDrawing();
    
    if (bgTexture.id != 0) {
        DrawTexture(bgTexture, 0, 0, WHITE);
    }

        // Start Game button
    if (ui.button(1, "Start Game", {611, 565, 258, 58}, 48)) {
        Globals::sceneManager->switchScene(1); // go to Stage 1
    }

    // Leaderboard button
    if (ui.button(2, "Leaderboard", {611, 635, 258, 58}, 48)) {
        Globals::sceneManager->switchScene(3); // go to LeaderBoard scene
    }

    // Settings button
    if (ui.button(3, "Settings", {646, 705, 188, 58}, 48)) {
        // open settings
    }
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