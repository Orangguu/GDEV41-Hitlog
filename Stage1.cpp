#include "Stage1.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "ResourceManager.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
vector<Bullet> bullets;
void Stage1::update(float delta) {
    bulletTimer += delta;

    // SHOOT — create a NEW bullet
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && bulletTimer >= bulletCooldown) {
        Bullet b;

        Vector2 startPos = {
            player.pos.x + player.width * 2.5f,
            player.pos.y + player.height * 2.5f
        };

        b.fire(startPos, GetMousePosition());
        bullets.push_back(b);

        bulletTimer = 0;
    }

    // UPDATE ALL BULLETS
    for (auto &b : bullets)
        b.update(delta);

    // REMOVE INACTIVE BULLETS
    bullets.erase(
        remove_if(bullets.begin(), bullets.end(),
            [](const Bullet &b) { return !b.active; }),
        bullets.end()
    );

    player.update(delta);
}


void Stage1::draw() {
    BeginDrawing();
    DrawTexture(bgTexture, 0, 0, WHITE);
    for (Bullet &bullet : bullets) {
        bullet.draw();
    }
    player.draw();
    EndDrawing();
}

void Stage1::enter() {
    try {
        // Load background texture
        bgTexture = ResourceManager::getTexture("assets/backgrounds/tabletop-bg.png");
        
        // Load player texture
        player.animTexture = ResourceManager::getTexture("assets/entities/eggsy-sheet.png");
        
        // Optionally initialize width/height from the texture
        player.width = static_cast<float>(player.animTexture.width / 6); // assuming 5 frames in X
        player.height = static_cast<float>(player.animTexture.height / 6); // adjust rows

        player.texturesLoaded = true;

        ResourceManager::getTexture("assets/entities/enemy-sheet.png");
    } catch (const std::exception& e) {
        std::cerr << "Failed to load Stage1 assets: " << e.what() << std::endl;
    }
}

void Stage1::exit() {
}