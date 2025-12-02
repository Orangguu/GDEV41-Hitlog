#pragma once
#include "Scene.hpp"
#include "UILibrary.hpp"
#include "raylib.h"

class GameOver : public Scene {
    private:
        UILibrary ui;
        Texture2D bgTexture;
        int finalKills = 0;
        float finalTime = 0.0f;
    
    public:
        void setStats(int kills, float time) { 
            finalKills = kills; 
            finalTime = time; 
        }
        void enter() override;
        void update(float delta) override;
        void draw() override;
        void exit() override;
};