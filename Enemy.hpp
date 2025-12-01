#pragma once
#include "raylib.h"
#include "Player.hpp"
#include <unordered_map>
#include <string>
#include <vector>

struct Enemy {
    int health;
    int speed;

    //enemyType 1 for BACON
    //enemyType 2 for BREAD
    int enemyType = 1; 
    float radius = 80.0f;
    bool active = true;
    Vector2 pos;
    Player targetPlayer;

    //Textures
    static Texture2D defaultTexture;
    Texture2D texture;
    bool texturesLoaded = false;
    int spriteScale = 5;
    int spriteFPS = 10;

    //32 by 32 sprite
    float frameSize = 32.0f;
    int frameX;
    int frameY;
    float animTimer = 0.0f;
    
    void update(float dt);
    void draw() const;
    void spawn();
    void die();
};