#include "Stage1.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "globals.hpp"
#include "ResourceManager.hpp"
#include <vector>
#include <iostream>
#include <algorithm>


float spawnTimer = 0.0f;


//HELPER FUNCTIONS
bool checkCollision(const Bullet &b, const Enemy &e) {
    return CheckCollisionCircles(b.pos, b.radius, e.pos, e.radius);
}

using namespace std;
//vector<Enemy> enemies;
void Stage1::update(float delta) {
    // Check for game over
    if (player.health <= 0) {
        if (gameOverScene) {
            gameOverScene->setStats(killCount, survivalTime);
        }
        Globals::sceneManager->switchScene(2); // Switch to game over scene
        return;
    }
    
    // Update survival time
    survivalTime += delta;
    
    bulletTimer += delta;

    // PLAYER BULLET HANDLING
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && bulletTimer >= bulletCooldown) {
        Bullet b;
        b.isEnemyBullet = false;
        Vector2 startPos = {
            player.pos.x,
            player.pos.y
        };

        b.fire(startPos, GetMousePosition());
        bullets.push_back(b);

        bulletTimer = 0;
    }

    // UPDATE ALL BULLETS
    for (Bullet &b : bullets)
        b.update(delta);

    // ENEMY SPAWNING
    spawnTimer += delta;
    if (spawnTimer >= 3.0f){
        spawnTimer = 0;

        enemies.emplace_back();
        Enemy& e = enemies.back();
        int randomType = (rand() % 2) + 1;
        e.spawn(randomType);
    }

    // UPDATE ENEMIES & BACON SHOOTING
    for (Enemy &e : enemies){
        e.targetPlayer = &player;
        e.update(delta);
        
        // bacon shoots bullets
        if (e.enemyType == 1 && e.shootTimer >= e.shootCooldown) {
            float distanceToPlayer = Vector2Distance(e.pos, player.pos);
            if (distanceToPlayer <= e.shootRange) {
                Bullet b;
                b.isEnemyBullet = true;
                b.radius = 15.0f;
                b.speed = 400;
                b.fire(e.pos, player.pos);
                bullets.push_back(b);
                e.shootTimer = 0.0f;
            }
        }
    }

    // PLAYER BULLET vs ENEMY COLLISION
    for (Bullet &b : bullets) {
        if (b.isEnemyBullet) continue; // skip enemy bullets
        
        for (Enemy &e : enemies) {
            if (!b.active || !e.active) continue;
            if (CheckCollisionCircles(b.pos, b.radius, e.pos, e.radius)) {
                b.active = false;
                e.health -= 25;
                if (e.health <= 0) {
                    e.active = false;
                    killCount++; // increment kill counter
                }
            }
        }
    }

    // ENEMY BULLET vs PLAYER COLLISION
    for (Bullet &b : bullets) {
        if (!b.isEnemyBullet || !b.active) continue;
        
        if (CheckCollisionCircles(b.pos, b.radius, player.pos, player.radius)) {
            b.active = false;
            player.health -= 1; // enemy bullets deal 1 damage
        }
    }

    // REMOVE DEAD ENEMIES
    enemies.erase(
        remove_if(enemies.begin(), enemies.end(),
            [](const Enemy &e) { return !e.active; }),
        enemies.end()
    );

    // REMOVE INACTIVE BULLETS
    bullets.erase(
        remove_if(bullets.begin(), bullets.end(),
            [](const Bullet &b) { return !b.active; }),
        bullets.end()
    );

    player.update(delta);
    hud.update(delta);
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
    hud.draw();
    EndDrawing();
}

void Stage1::enter() {
    try {
        // reset game state
        killCount = 0;
        survivalTime = 0.0f;
        player.health = 6;
        player.pos = {750, 500}; // centre of screen
        bullets.clear();
        enemies.clear();
        // load background texture
        bgTexture = ResourceManager::getTexture("assets/backgrounds/tabletop-bg.png");
        
        // load player texture
        player.animTexture = ResourceManager::getTexture("assets/entities/eggsy-sheet.png");
        player.texturesLoaded = true;
        
        // load enemy texture
        Enemy::defaultTexture = ResourceManager::getTexture("assets/entities/enemy-sheet.png");
    
        // load bullet texture
        Bullet::defaultTexture = ResourceManager::getTexture("assets/entities/bullet.png");

    } catch (const std::exception& e) {
        std::cerr << "Failed to load Stage1 assets: " << e.what() << std::endl;
    }

    hud.setStage(this);
}

void Stage1::exit() {
}

