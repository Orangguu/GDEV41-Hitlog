#pragma once
#include "UILibrary.hpp"
#include "raylib.h"

class HUD  {
    private:
        UILibrary ui;

    public:
        void update(float delta);
        void draw();
};