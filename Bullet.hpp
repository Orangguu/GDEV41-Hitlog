#pragma once
#include "raylib.h"

struct Bullet {
    Vector2 pos = {0, 0};
    Vector2 dir = {0, 0};   // normalized direction
    int speed = 700;
    float radius = 20.0f;
    float rotation = 0.0f;
    bool active = false;     // true if the bullet is in play

    float spriteScale = 2.0f;
    Vector2 frameSize = {30, 30};

    static Texture2D defaultTexture;  // <- new shared texture
    Texture2D texture;
    bool texturesLoaded = false;

    // Fire bullet from a position towards a target
    void fire(Vector2 startPos, Vector2 target);

    // Update bullet position
    void update(float dt);

    // Draw bullet
    void draw() const;
};
