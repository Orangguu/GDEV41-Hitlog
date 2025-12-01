#include "Stage1.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "ResourceManager.hpp"
#include <vector>
#include <iostream>
#include <algorithm>


float spawnTimer = 0.0f;

using namespace std;
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

    spawnTimer += delta;
    if (spawnTimer >= 3.0f){
        spawnTimer = 0;

        enemies.emplace_back();        // NEW ENEMY IN VECTOR
        Enemy& e = enemies.back();     // REFERENCE IT
        e.enemyType = 1;
        e.spawn();
    }

    enemies.erase(
        remove_if(enemies.begin(), enemies.end(),
            [](const Enemy &e) { return !e.active; }),
        enemies.end()
    );
    // UPDATE PLAYER
    for (Enemy &e : enemies){
        e.targetPlayer = player;
        e.update(delta);
    }

    player.update(delta);
}


void Stage1::draw() {
    BeginDrawing();
    DrawTexture(bgTexture, 0, 0, WHITE);
    for (Bullet &bullet : bullets) {
        bullet.draw();
    }
    for (Enemy &enemy : enemies) {
        enemy.draw();
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
        player.texturesLoaded = true;
        
        // Load enemy texture
        Enemy::defaultTexture = ResourceManager::getTexture("assets/entities/enemy-sheet.png");
    
        // Load bullet texture
        Bullet::defaultTexture = ResourceManager::getTexture("assets/entities/bullet.png");

    } catch (const std::exception& e) {
        std::cerr << "Failed to load Stage1 assets: " << e.what() << std::endl;
    }
}

void Stage1::exit() {
}

Vector2 Stage1::getPlayerPos() {
    return {Stage1::player.pos.x, Stage1::player.pos.y};
}
