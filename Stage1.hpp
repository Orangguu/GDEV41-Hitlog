#pragma once
#include "Player.hpp"
#include "Bullet.hpp"

struct Stage1 {
    int WINDOW_WIDTH = 0;
    int WINDOW_HEIGHT = 0;

    float bulletCooldown = 0.5f;
    float bulletTimer = bulletCooldown;

    Bullet bullet;
    Player player;

    Stage1(int windowWidth, int windowHeight);
    void update(float delta);
    void draw() const;
};