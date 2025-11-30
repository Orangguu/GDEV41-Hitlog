#pragma once
#include "UILibrary.hpp"

struct MainMenu {
    int WINDOW_WIDTH = 0;
    int WINDOW_HEIGHT = 0;

    UILibrary ui;

    MainMenu(int windowWidth, int windowHeight);
    void update(float delta);
};