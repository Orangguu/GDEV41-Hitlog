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
    int maxHealth = 6;
    int health;
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
    float baseAttackCd = 0.4f;
    float attackCd = baseAttackCd;

    // Textures
    Texture2D animTexture;
    bool texturesLoaded = false;
    int spriteScale = 5;
    int spriteFPS = 4;

    // On hit animation
    float hitFlashTimer = 0.0f;
    float hitFlashDuration = 0.2f; // 200ms flash
    bool wasHit = false;

    // Dashing
    bool is_dashing = false;
    float dashDistance = 200.0f;
    float dashDuration = 0.2f;     // How long the dash lasts (seconds)
    float dashTimer = 0.0f;
    float dashCooldown = 1.0f;     // Time before next dash
    float dashCooldownTimer = 0.0f;
    Vector2 dashDir = {0, 0};      // Direction of current dash

    void update(float dt);
    void draw() const;
    void takeDamage(int dmg);
};
