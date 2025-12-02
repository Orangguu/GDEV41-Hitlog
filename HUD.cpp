#include "HUD.hpp"
#include "Stage1.hpp"
#include <string>

void HUD::update(float delta) {
    // get player current health and max health
}

void HUD::draw() {
    DrawRectangleRec({0, 0, 1500, 113}, BLACK);
    ui.text(0, "Health", {48, 22, 141, 69}, 64, WHITE);
    
    if (stage) {
        int health = stage->getPlayerHealth();
        int maxHealth = stage->getPlayerMaxHealth();
        Color healthColor = (health > 2) ? GREEN : RED;
        ui.progressBar(1, {215, 22, 400, 69}, health, maxHealth, healthColor);
        
        ui.text(2, "Kills:", {1252, 22, 90, 69}, 64, WHITE);
        ui.text(3, std::to_string(stage->getKillCount()), {1389, 22, 83, 69}, 64, WHITE);
        
        // survival time
        int minutes = (int)stage->getSurvivalTime() / 60;
        int seconds = (int)stage->getSurvivalTime() % 60;
        std::string timeStr = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
        ui.text(4, timeStr, {650, 22, 200, 69}, 48, WHITE);
    }
}