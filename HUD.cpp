#include "HUD.hpp"

void HUD::update(float delta) {
    // get player current health and max health
}

void HUD::draw() {
    DrawRectangleRec({0, 0, 1500, 113}, BLACK);
    ui.text(0, "Health", {48, 22, 141, 69}, 64, WHITE);
    ui.progressBar(1, {215, 22, 547, 69}, 80, 100, GREEN); // TODO: input player values here
    ui.text(2, "Kills:", {1252, 22, 90, 69}, 64, WHITE);
    ui.text(3, "999", {1389, 22, 83, 69}, 64, WHITE); // TODO: input values here
}