#include "globals.hpp"

// sceneManager is properly initialized in main.cpp
// it will not worked if initialized here
// (for reasons i am yet to discover)

int Globals::WINDOW_HEIGHT = 900;
int Globals::WINDOW_WIDTH = 1200;
SceneManager* Globals::sceneManager = nullptr;