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
    int totalSeconds = (int)finalTime;
    int score = (finalKills * 50) + (totalSeconds * 10);

    // score = (kills x 50) + (time x 10)
    ui.text(0, "Score:", {70, 500, 200, 80}, 64, Color{255, 200, 100, 255});
    ui.text(1, std::to_string(score), {240, 500, 200, 80}, 64, Color{255, 200, 100, 255});
    
    // kills
    ui.text(3, "Kills:", {60, 610, 200, 60}, 56, WHITE);
    ui.text(4, std::to_string(finalKills), {230, 610, 150, 60}, 56, Color{255, 200, 100, 255});

    // time survived
    int minutes = (int)finalTime / 60;
    int seconds = (int)finalTime % 60;
    std::string timeStr = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
    
    ui.text(5, "Time:", {70, 710, 200, 60}, 56, WHITE);
    ui.text(6, timeStr, {230, 710, 150, 60}, 56, Color{255, 200, 100, 255});
    
    // right | navigation
    // try again button
    if (ui.button(1, "Try Again", {1060, 580, 300, 70}, 56)) {
        Globals::sceneManager->switchScene(1); // restart Stage 1
    }
    
    // main menu button
    if (ui.button(2, "Main Menu", {1060, 710, 300, 70}, 56)) {
        Globals::sceneManager->switchScene(0); // go to main menu
    }
    
    EndDrawing();
}

void GameOver::exit() {}