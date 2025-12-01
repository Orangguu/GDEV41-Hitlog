#pragma once
#include "Enemy.hpp"
#include "globals.hpp"
#include "raylib.h"
#include <unordered_map>
#include <cstdlib>

class EnemyFollower : public Enemy {
    private:
        int currentState = -1;
        std::unordered_map<int, Vector2> spawnLocations;

    public:
        void spawn() override;
        void update(float delta) override;
        void draw() override;
        void die() override;
};