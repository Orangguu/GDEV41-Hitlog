#include "Enemy.hpp"
#include <raymath.h>
// states:
// - following
// - attacking

// reference for randomizer:
// https://medium.com/@manikireeti007/random-number-generator-in-c-32896406bb1a

// assuming there is a spritesheet
// sprites in the sheet should be unraveled into a vector
// then inserted into "sprites" with the name of the animation

Texture2D Enemy::defaultTexture = {0};
void Enemy::spawn() {
    if(enemyType == 1){
        health = 100;
        speed = 20;
        frameX = 0;
    }
    if(enemyType == 2){
        health = 50;
        speed = 100;
        frameY = 2;
    }

    bool isSpawningTop = (rand() > (RAND_MAX / 2)) ? true : false;
    bool isSpawningLeft = (rand() > (RAND_MAX / 2)) ? true : false;
    float spawnPosX = 0;
    float spawnPosY = 0;
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();
    if (isSpawningTop) {
        spawnPosY = rand() % (0-(-150)+1) + (-150);
    }
    else {
        spawnPosY = rand() % (screenHeight-(screenHeight+150)+1) + (screenHeight+150);
    }
    if (isSpawningLeft) {
        spawnPosX = rand() % (0-(-150)+1) + (-150);
    }
    else {
        spawnPosX = rand() % (screenWidth-(screenWidth+150)+1) + (screenWidth+150);
    }
    pos = {spawnPosX, spawnPosY};


// Define static texture storage
    texture = defaultTexture;
    texturesLoaded = true;
}


void Enemy::update(float delta) {
    Vector2 enemyCenter = { pos.x, pos.y};
    Vector2 playerCenter = { targetPlayer.pos.x + targetPlayer.width / 2.0f,
                         targetPlayer.pos.y + targetPlayer.height / 2.0f };
    
    // Vector2 direction = Vector2Normalize(Vector2Subtract(playerCenter, enemyCenter));
    Vector2 direction = Vector2Normalize(Vector2Subtract(targetPlayer.pos, pos));

    float speed = 150.0f;
    pos = Vector2Add(pos, Vector2Scale(direction, speed * delta));

    animTimer += delta;
    if (animTimer >= 1.0f / spriteFPS) {
        animTimer = 0;
        frameX++;
        if(enemyType == 1 && frameX == 9) frameX = 0;
        if(enemyType == 2 && frameX == 13) frameX = 0;
    }
}

void Enemy::draw() const{
    if (texturesLoaded) {
        Rectangle origFrame = { frameX * frameSize, frameY * frameSize, frameSize, frameSize };        
        float nudgeX = -frameSize / 2 * spriteScale;
        float nudgeY = -frameSize / 2 * spriteScale;
        Rectangle dest = { pos.x + nudgeX, pos.y + nudgeY, frameSize * spriteScale, frameSize * spriteScale };
        DrawTexturePro(texture, origFrame, dest, {0, 0}, 0, WHITE);

        // Debug: show actual pos
        // DrawCircleV(pos, radius, ORANGE);
    } else {
        DrawCircleV(pos, radius, ORANGE);
    }
}

void Enemy::die() {
}