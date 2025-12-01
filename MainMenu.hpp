#pragma once
#include "globals.hpp"
#include "UILibrary.hpp"
#include "Scene.hpp"

class MainMenu : public Scene {
    private:
        UILibrary ui;
        Texture2D bgTexture;
    
    public:
        Sound bgMusic;
        void enter() override;
        void update(float delta) override;
        void draw() override;
        void exit() override;
};