#pragma once
#include <raylib.h>

struct Bullet {
    Vector2 pos = {0, 0};
    Vector2 dir = {0, 0};   // normalized direction
    int speed = 500;
    int radius = 5;
    bool active = false;     // true if the bullet is in play

    // Fire bullet from a position towards a target
    void fire(Vector2 startPos, Vector2 target);

    // Update bullet position
    void update(float dt);

    // Draw bullet
    void draw() const;
};
