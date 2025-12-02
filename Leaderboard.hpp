#pragma once
#include "Scene.hpp"
#include "UILibrary.hpp"
#include "raylib.h"

class LeaderBoard : public Scene {
    private:
        UILibrary ui;
        Texture2D bgTexture;
        std::string username = "";
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