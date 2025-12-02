#include "GameOver.hpp"
#include "globals.hpp"
#include "ResourceManager.hpp"

void GameOver::enter() {
    try {
        bgTexture = ResourceManager::getTexture("assets/backgrounds/gameover.png");
    } catch (const std::exception& e) {}
}

void GameOver::update(float delta) {}

void GameOver::draw() {
    BeginDrawing();
    ClearBackground(Color{20, 20, 30, 255});
    
    if (bgTexture.id != 0) {
        DrawTexture(bgTexture, 0, 0, WHITE);
    } else {
        // if texture fails to load
        ClearBackground(Color{20, 20, 30, 255});
    }
    
    // main menu button
    if (ui.button(1, "Main Menu", {611, 500, 258, 58}, 48)) {
        Globals::sceneManager->switchScene(0); // go to main menu
    }
    
    // retry button
    if (ui.button(2, "Try Again", {611, 600, 258, 58}, 48)) {
        Globals::sceneManager->switchScene(1); // restart stage 1
    }
    
    EndDrawing();
}

void GameOver::exit() {}