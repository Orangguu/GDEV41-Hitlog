#pragma once
#include "raylib.h"
#include "Player.hpp"
#include <unordered_map>
#include <string>
#include <vector>

struct Enemy {
    int health;
    int speed;
    int enemyType = 1;
    float width = 30.0f;
    float height = 30.0f;
    bool active = true;
    Vector2 size;
    Vector2 pos;
    Player targetPlayer;

    //Textures
    static Texture2D defaultTexture;
    Texture2D texture;
    bool texturesLoaded = false;
    int spriteScale = 5;
    int spriteFPS = 4;
    int frameX;
    int frameY;
    
    void update(float dt);
    void draw() const;
    void spawn();
    void die();
};