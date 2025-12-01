#pragma once
#include "Scene.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include <raylib.h>
#include "Enemy.hpp"
#include <vector>
#include "HUD.hpp"

class Stage1 : public Scene {
    private:
        float bulletCooldown = 0.5f;
        float bulletTimer = bulletCooldown;
        Bullet bullet;
        Player player;
        std::vector<Bullet> bullets;
        std::vector<Enemy> enemies;
        HUD hud;

        Texture2D bgTexture;
    
    public:
        void enter() override;
        void update(float delta) override;
        void draw() override;
        void exit() override;
        Vector2 getPlayerPos();
};