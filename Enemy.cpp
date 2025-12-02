#include "Enemy.hpp"
#include <raymath.h>
#include <iostream>

Texture2D Enemy::defaultTexture = {0};
void Enemy::spawn(int type) {
    enemyType = type;
    frameX = 0;
    if(enemyType == 1){ //Bread
        health = 75;
        speed = 50;
        frameY = 2;
    }
    if(enemyType == 2){ //Bacon
        health = 50;
        speed = 20;
        frameY = 0;
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

    facingRight = !isSpawningLeft;


// Define static texture storage
    texture = defaultTexture;
    texturesLoaded = true;
}


void Enemy::update(float delta) {
    Vector2 direction = Vector2Normalize(Vector2Subtract(targetPlayer->pos, pos));
    float distanceToPlayer = Vector2Distance(pos, targetPlayer->pos);

    // update facing direction based on horizontal movement
    facingRight = (direction.x >= 0);

   
    // BREAD BEHAVIOUR (type 1): chase and deal melee damage
    if (enemyType == 1) {
        float speedValue = 150.0f;
        pos = Vector2Add(pos, Vector2Scale(direction, speedValue * delta));
        
        // check collision with player
        isCollidingWithPlayer = CheckCollisionCircles(pos, radius, targetPlayer->pos, targetPlayer->radius);
        
        if (isCollidingWithPlayer) {
            collisionTimer += delta;
            
            // deal damage every 1 second
            if (collisionTimer >= damageInterval) {
                targetPlayer->takeDamage(meleeDamage);
                collisionTimer = 0.0f; // reset for next damage tick
            }
        } else {
            // reset timer if not colliding
            collisionTimer = 0.0f;
        }
    }
    else if  (enemyType == 2) {// BACON BEHAVIOUR (type 2): shoot from range
        // move towards player until in range
        if (distanceToPlayer > shootRange) {
            float speedValue = 150.0f;
            pos = Vector2Add(pos, Vector2Scale(direction, speedValue * delta));
        }
        // update shoot timer
        shootTimer += delta;
    }

    // animate onHit
    if (hitFlashTimer > 0) {
        hitFlashTimer -= delta;
        if (hitFlashTimer < 0) hitFlashTimer = 0;
    }

    // animate frames
    animTimer += delta;
    if (animTimer >= 1.0f / spriteFPS) {
        animTimer = 0;
        frameX++;
        if(enemyType == 1 && frameX >= 14) frameX = 0; // bacon has 10 frames
        if(enemyType == 2 && frameX >= 10) frameX = 0; // bread has 14 frames
    }
    
}

void Enemy::draw() const {
    if (!texturesLoaded) {
        DrawCircleV(pos, radius, ORANGE);
        return;
    }

    // decide which row in the sprite sheet
    int row = 0;
    if(enemyType == 1) { // bread
        row = facingRight ? 2 : 3;
    } else if(enemyType == 2) { // bacon
        row = facingRight ? 0 : 1;
    }

    Rectangle origFrame = { frameX * frameSize, row * frameSize, frameSize, frameSize };

    float nudgeX = -frameSize / 2 * spriteScale;
    float nudgeY = -frameSize / 2 * spriteScale;

    Rectangle dest = { pos.x + nudgeX, pos.y + nudgeY, frameSize * spriteScale, frameSize * spriteScale };

    DrawTexturePro(texture, origFrame, dest, {0,0}, 0, WHITE);

    if (hitFlashTimer > 0) {
        Color flash = {255, 125, 125, (unsigned char)(200 * (hitFlashTimer / hitFlashDuration))};
        BeginBlendMode(BLEND_ADDITIVE);
        DrawTexturePro(texture, origFrame, dest, {0,0}, 0, flash);
        EndBlendMode();
    }
}

void Enemy::die() {
}

void Enemy::takeDamage(int dmg){
    health -= dmg;
    wasHit = true;
    hitFlashTimer = hitFlashDuration;
}