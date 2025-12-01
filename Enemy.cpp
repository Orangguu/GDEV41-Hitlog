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
        size = {100, 100};
    }
    if(enemyType == 2){
        health = 50;
        speed = 100;
        size = {50, 50};
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
    Vector2 direction = Vector2Normalize(Vector2Subtract(targetPlayer.pos, pos));
    float speed = 150.0f;
    pos = Vector2Add(pos, Vector2Scale(direction, speed * delta));
}

void Enemy::draw() const{
    if (texturesLoaded) {
        //Player frames
        Rectangle origFrame = { frameX * width, frameY * height, width, height };
        Rectangle dest = { pos.x, pos.y, width * spriteScale, height * spriteScale };
        DrawTexturePro(texture, origFrame, dest, {0, 0}, 0, WHITE);
    } else {
        DrawCircleV(pos, width, ORANGE);
    }
}

void Enemy::die() {
}