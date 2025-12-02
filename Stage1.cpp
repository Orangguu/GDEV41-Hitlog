#include "Stage1.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "globals.hpp"
#include "ResourceManager.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

float baseSpawnInterval = 3.0f;    // starting spawn interval
float minSpawnInterval  = 0.5f;    // minimum spawn interval
float spawnTimer = 0.0f;


//HELPER FUNCTIONS
bool checkCollision(const Bullet &b, const Enemy &e) {
    return CheckCollisionCircles(b.pos, b.radius, e.pos, e.radius);
}

using namespace std;
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
        Vector2 startPos = { player.pos.x, player.pos.y };
        b.fire(startPos, GetMousePosition());
        bullets.push_back(b);
        bulletTimer = 0;
    }

    // UPDATE ALL BULLETS
    for (Bullet &b : bullets)
        b.update(delta);

    // ===== ENEMY SPAWNING WITH SCALING =====
    spawnTimer += delta;

    // Smooth spawn interval decreases as time passes
    float spawnInterval = baseSpawnInterval - (survivalTime * 0.05f); // slower acceleration
    if (spawnInterval < minSpawnInterval) spawnInterval = minSpawnInterval;

    // Spawn single enemies over time
    if (spawnTimer >= spawnInterval) {
        spawnTimer = 0;

        enemies.emplace_back();
        Enemy& e = enemies.back();

        // Progressive type unlock
        int maxType = 1;
        if (survivalTime > 20) maxType = 2; //Introduce bacon after surviving 20 seconds
        // Add more types if needed
        int randomType = (rand() % maxType) + 1;
        e.spawn(randomType);
    }

    // UPDATE ENEMIES & BACON SHOOTING
    for (Enemy &e : enemies){
        e.targetPlayer = &player;
        e.update(delta);
        
        // bacon shoots bullets
        if (e.enemyType == 2 && e.shootTimer >= e.shootCooldown) {
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
                e.takeDamage(25);
                if (e.health <= 0) {
                    e.active = false;
                    killCount++;
                }
            }
        }
    }

    // ENEMY BULLET vs PLAYER COLLISION
    for (Bullet &b : bullets) {
        if (!b.isEnemyBullet || !b.active) continue;
        if (CheckCollisionCircles(b.pos, b.radius, player.pos, player.radius)) {
            b.active = false;
            player.takeDamage(1);
        }
    }

    // REMOVE DEAD ENEMIES & INACTIVE BULLETS
    enemies.erase(remove_if(enemies.begin(), enemies.end(),
                            [](const Enemy &e){ return !e.active; }),
                  enemies.end());

    bullets.erase(remove_if(bullets.begin(), bullets.end(),
                            [](const Bullet &b){ return !b.active; }),
                  bullets.end());

    player.update(delta);
    hud.update(delta);

    if (Globals::music_enabled && !IsSoundPlaying(bgMusic)) {
        PlaySound(bgMusic);
    }
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
        player.health = player.maxHealth;
        player.pos = {750, 500}; // centre of screen
        player.is_dashing = false;
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

        // load music
        bgMusic = ResourceManager::getSound("./assets/music/music_stage_1.wav");
        if (Globals::music_enabled) {
            PlaySound(bgMusic);
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to load Stage1 assets: " << e.what() << std::endl;
    }

    hud.setStage(this);
}

void Stage1::exit() {
    ResourceManager::unloadAll();
}

