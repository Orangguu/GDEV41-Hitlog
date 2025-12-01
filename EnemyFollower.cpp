#include "EnemyFollower.hpp"

// states:
// - following
// - attacking

// reference for randomizer:
// https://medium.com/@manikireeti007/random-number-generator-in-c-32896406bb1a

// assuming there is a spritesheet
// sprites in the sheet should be unraveled into a vector
// then inserted into "sprites" with the name of the animation

void EnemyFollower::spawn() {
    health = 100;
    speed = 20;
    size = {100, 100};
    currentState = 0; // following
    targetPlayer = Stage1::player; // TODO: get current player instance

    std::vector<Texture*> followSprites;
    Texture followSpriteSheet = LoadTexture("./assets/sprites/enemy/enemy_placeholder.png");
    followSprites.push_back(&followSpriteSheet);
    animations.insert({"follow", followSprites});
    currentAnimation = "follow";
    currentAnimationFrame = 0;

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
        spawnPosY = rand() % (screenWidth-(screenWidth+150)+1) + (screenWidth+150);
    }
    pos = {spawnPosX, spawnPosY};
}

void EnemyFollower::update(float delta) {
    Vector2 playerPos = Globals::sceneManager->getActiveScene()->ge;
}

void EnemyFollower::draw() {
    BeginDrawing();
    DrawTextureEx(*(animations.at("follow").at(currentAnimationFrame)), pos, 0, 1, WHITE);
    EndDrawing();
}

void EnemyFollower::die() {
}