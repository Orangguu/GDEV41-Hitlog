#include "Stage1.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "ResourceManager.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
vector<Bullet> bullets;
//vector<Enemy> enemies;
void Stage1::update(float delta) {
    bulletTimer += delta;

    // BULLET HANDLING
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
    for (Bullet &b : bullets)
        b.update(delta);

    // REMOVE INACTIVE BULLETS
    bullets.erase(
        remove_if(bullets.begin(), bullets.end(),
            [](const Bullet &b) { return !b.active; }),
        bullets.end()
    );

    // BULLET COLLISION (WALL AND ENEMY)

    // ENEMY COLLISION (PLAYER)
    /*
        for(Enemy &e : enemies)
            e.update(delta)
            e.checkCollision

        // REMOVE DEAD ENEMIES
        enemies.erase(
            remove_if(bullets.begin(), bullets.end(),
                [](const Bullet &b) { return !b.active; }),
            bullets.end()
        );
    */

    
    // UPDATE PLAYER
    player.update(delta);
    hud.update(delta);
}


void Stage1::draw() {
    BeginDrawing();
    DrawTexture(bgTexture, 0, 0, WHITE);
    for (Bullet &bullet : bullets) {
        bullet.draw();
    }
    player.draw();
    hud.draw();
    EndDrawing();
}

void Stage1::enter() {
    try {
        // Load background texture
        bgTexture = ResourceManager::getTexture("assets/backgrounds/tabletop-bg.png");
        
        // Load player texture
        player.animTexture = ResourceManager::getTexture("assets/entities/eggsy-sheet.png");
        player.texturesLoaded = true;
        
        //Enemy::animTexture = ResourceManager::getTexture("assets/entities/enemy-sheet.png");
        
        // Load bullet texture
        Bullet::defaultTexture = ResourceManager::getTexture("assets/entities/bullet.png");

    } catch (const std::exception& e) {
        std::cerr << "Failed to load Stage1 assets: " << e.what() << std::endl;
    }
}

void Stage1::exit() {
}
