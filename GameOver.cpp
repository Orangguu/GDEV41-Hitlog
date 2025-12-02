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
    
    if (bgTexture.id != 0) {
        DrawTexture(bgTexture, 0, 0, WHITE);
    } else {
        // if texture fails to load
        ClearBackground(Color{20, 20, 30, 255});
    }

    // left | stats display
    ui.text(0, "My Stats", {80, 400, 400, 80}, 64, Color{255, 200, 100, 255});
    
    // kills
    ui.text(3, "Kills:", {70, 510, 200, 60}, 56, WHITE);
    ui.text(4, std::to_string(finalKills), {250, 510, 150, 60}, 56, Color{255, 200, 100, 255});

    // time survived
    int minutes = (int)finalTime / 60;
    int seconds = (int)finalTime % 60;
    std::string timeStr = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
    
    ui.text(5, "Time:", {80, 610, 200, 60}, 56, WHITE);
    ui.text(6, timeStr, {250, 610, 150, 60}, 56, Color{255, 200, 100, 255});
    
    // right | navigation
    // try again button
    if (ui.button(1, "Try Again", {1050, 480, 300, 70}, 56)) {
        Globals::sceneManager->switchScene(1); // restart Stage 1
    }
    
    // main menu button
    if (ui.button(2, "Main Menu", {1050, 590, 300, 70}, 56)) {
        Globals::sceneManager->switchScene(0); // go to main menu
    }
    
    EndDrawing();
}

void GameOver::exit() {}