#pragma once
#include "Scene.hpp"
#include "UILibrary.hpp"
#include "raylib.h"
#include <fstream>
#include <string>
#include <iostream>

class GameOver : public Scene {
    private:
        UILibrary ui;
        Texture2D bgTexture;
        int finalKills = 0;
        float finalTime = 0.0f;
    
        void saveScore(std::string playerName, float score) {
            std::string name = playerName.empty() ? "Anonymous" : playerName;
            std::ofstream file("scores.txt", std::ios::app);
            if (file.is_open()) {
                file << name << " " << score << "\n";
                file.close();
            } else {
                std::cerr << "Failed to open scores.txt" << std::endl;
            }
        }
    public:
        Sound bgMusic;
        void setStats(int kills, float time) { 
            finalKills = kills; 
            finalTime = time; 
        }
        void enter() override;
        void update(float delta) override;
        void draw() override;
        void exit() override;
};