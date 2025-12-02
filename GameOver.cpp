#include "GameOver.hpp"
#include "globals.hpp"
#include "ResourceManager.hpp"
#include <string>
#include <iostream>

InputField playerName;

void GameOver::enter() {
    playerName = {"", 12, {100, 400, 300, 50}, false, "Enter name..."}; //Resets the fields
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
    ui.text(2, "Kills:", {60, 610, 200, 60}, 56, WHITE);
    ui.text(3, std::to_string(finalKills), {230, 610, 150, 60}, 56, Color{255, 200, 100, 255});

    // time survived
    int minutes = (int)finalTime / 60;
    int seconds = (int)finalTime % 60;
    std::string timeStr = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
    
    ui.text(4, "Time:", {70, 710, 200, 60}, 56, WHITE);
    ui.text(5, timeStr, {230, 710, 150, 60}, 56, Color{255, 200, 100, 255});
    
    // right | navigation

    // Player stats
    ui.input(6, playerName, 40, WHITE, ORANGE);

    // try again button
    if (ui.button(7, "Save Score", {1060, 580, 300, 70}, 56)) {
        std::cout << " Saving score!!!!";
        saveScore(playerName.text, score);
        Globals::sceneManager->switchScene(3); // Save score, and move to leaderboard name left empty if no name
    }
    
    // main menu button
    if (ui.button(8, "Main Menu", {1060, 710, 300, 70}, 56)) {
        Globals::sceneManager->switchScene(0); // go to main menu
    }
    
    EndDrawing();
}

void GameOver::exit() {}