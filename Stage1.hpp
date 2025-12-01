#pragma once
#include "Scene.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

class Stage1 : public Scene {
    private:
        float bulletCooldown = 0.5f;
        float bulletTimer = bulletCooldown;
        Bullet bullet;
        Player player;
    
    public:
        void enter() override;
        void update(float delta) override;
        void draw() override;
        void exit() override;
};