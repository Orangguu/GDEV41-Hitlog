#pragma once
#include "Scene.hpp"
#include "UILibrary.hpp"
#include "raylib.h"

class GameOver : public Scene {
    private:
        UILibrary ui;
        Texture2D bgTexture;
    
    public:
        void enter() override;
        void update(float delta) override;
        void draw() override;
        void exit() override;
};