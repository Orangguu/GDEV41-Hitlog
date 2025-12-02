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


        // Instructions
        std::string controls = "WASD - Movement\nSPACE - Dash\nLEFT CLICK - Shoot";
        int screenW = GetScreenWidth();
        int screenH = GetScreenHeight();
        int padding = 20;
        float fontSize = 50;
        Color textColor = BLACK;

        // Measure total text height
        Vector2 textSize = MeasureTextEx(ui.font, "W", fontSize, 0); // approximate line height
        int lineHeight = (int)textSize.y;

        // Draw each line manually
        std::vector<std::string> lines = {"WASD - Movement", "SPACE - Dash", "LEFT CLICK - Shoot"};
        for (size_t i = 0; i < lines.size(); ++i) {
            Vector2 pos = {
                (float)(screenW - padding - MeasureTextEx(ui.font, lines[i].c_str(), fontSize, 0).x),
                (float)(screenH - padding - (lines.size() - i) * lineHeight)
            };
            DrawTextEx(ui.font, lines[i].c_str(), pos, fontSize, 0, textColor);
        }
    }
}