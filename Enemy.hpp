#pragma once
#include "raylib.h"
#include "Player.hpp"
#include <unordered_map>
#include <string>
#include <vector>

class Enemy {
    protected:
        int health;
        int speed;
        Vector2 size;
        Vector2 pos;
        std::unordered_map<std::string, std::vector<Texture*>> animations;
        std::unordered_map<std::string, Sound*> sfx;
        std::string currentAnimation;
        int currentAnimationFrame;
        Player targetPlayer;
    public:
        virtual void spawn() = 0;
        virtual void update(float delta) = 0;
        virtual void draw() = 0;
        virtual void die() = 0;
};