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
        Globals::sceneManager->switchScene(1); // Start game
    }

    // Leaderboard button
    if (ui.button(2, "Leaderboard", {611, 635, 258, 58}, 48)) {
        Globals::sceneManager->switchScene(3); // go to Leaderboard scene
    }

    // Settings button
    if (ui.button(3, Globals::music_enabled ? "Music: ON" : "Music: OFF", {646, 705, 188, 58}, 48)) {
        Globals::music_enabled = !Globals::music_enabled; // Toggle music on and off
    }
    EndDrawing();
}

void MainMenu::enter() {
    bgMusic = ResourceManager::getSound("./assets/music/music_main_menu.wav");
    bgTexture = ResourceManager::getTexture("assets/backgrounds/title-screen.png");
    if (Globals::music_enabled) {
        PlaySound(bgMusic);
    }
}

void MainMenu::update(float delta) {
    if (Globals::music_enabled && !IsSoundPlaying(bgMusic)) {
        PlaySound(bgMusic);
    }
    else if (!Globals::music_enabled){
        StopSound(bgMusic);
    }
}

void MainMenu::exit() {
    ResourceManager::unloadAll();
}