#pragma once
#include "raylib.h"

enum Direction {
    DOWN,
    DOWN_RIGHT,
    RIGHT,
    UP_RIGHT,
    UP,
    UP_LEFT,
    LEFT,
    DOWN_LEFT
};

struct Player {
    //TEMP
    float radius = 20.0f;
    Color color = BLUE;

    Vector2 pos = {200, 200};
    float width, height;
    int speed = 300;
    bool is_attacking = false;
    bool is_idle = true;
    Direction direction = DOWN;

    // Sprite animation
    int frameX = 0;
    int frameY = 0;
    float animTimer = 0.0f;

    // Textures
    Texture walkTexture;
    Texture attackTexture;
    int spriteScale = 5;
    int spriteFPS = 4;

    void update(float dt);
    void draw() const;
};
