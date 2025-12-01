#pragma once
#include "Scene.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include <raylib.h>

class Stage1 : public Scene {
    private:
        float bulletCooldown = 0.5f;
        float bulletTimer = bulletCooldown;
        Bullet bullet;
        Player player;

        Texture2D bgTexture;
    
    public:
        void enter() override;
        void update(float delta) override;
        void draw() override;
        void exit() override;
};