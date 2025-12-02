#pragma once
#include "UILibrary.hpp"
#include "raylib.h"

class HUD  {
    private:
        UILibrary ui;
        class Stage1* stage = nullptr; // to get game data

    public:
        void setStage(Stage1* s) { stage = s; }
        void update(float delta);
        void draw();
};