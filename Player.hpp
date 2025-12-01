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
    //Initial position
    float radius = 30.0f;
    Color color = BLUE;
    int health = 6;
    Vector2 pos;

    //Size of the grid
    float frameSize = 30.0f;
    float width = 30.0f;
    float height = 30.0f;
    int speed = 300;
    bool is_attacking = false;
    bool is_idle = true;
    Direction direction = DOWN;

    // Sprite animation
    int frameX = 0;
    int frameY = 1;
    
    float animTimer = 0.0f;
    float skillCd = 2.0f;
    float attackCd = 0.5f;

    // Textures
    Texture2D animTexture;
    bool texturesLoaded = false;
    int spriteScale = 5;
    int spriteFPS = 4;

    // On hit animation
    bool isHit = false;
    float hitTimer = 0.0f;
    float flashDuration = 0.15f; // seconds

    // Dashing
    bool is_dashing = false;
    float dashDistance = 300.0f;
    float dashDuration = 0.3f;     // How long the dash lasts (seconds)
    float dashTimer = 0.0f;
    float dashCooldown = 1.0f;     // Time before next dash
    float dashCooldownTimer = 0.0f;
    Vector2 dashDir = {0, 0};      // Direction of current dash

    void update(float dt);
    void draw() const;
};
