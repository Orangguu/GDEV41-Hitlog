#pragma once
#include "Scene.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "GameOver.hpp"
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

        int killCount = 0;
        float survivalTime = 0.0f;

        GameOver* gameOverScene = nullptr;
    
    public:
        Sound bgMusic;
        void enter() override;
        void update(float delta) override;
        void draw() override;
        void exit() override;
        Vector2 getPlayerPos();
        void setGameOverScene(GameOver* go) { gameOverScene = go; }

        int getKillCount() const { return killCount; }
        float getSurvivalTime() const { return survivalTime; }
        int getPlayerHealth() const { return player.health; }
        int getPlayerMaxHealth() const { return 6; }
};