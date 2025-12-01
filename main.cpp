#include "raylib.h"
#include "globals.hpp"
#include "Stage1.hpp"
#include "MainMenu.hpp"
#include "SceneManager.hpp"
#include <iostream>

const int FPS = 60;

int main() {
    SetTargetFPS(FPS);
    InitWindow(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT, "Pew Pew Pew");

    Globals::sceneManager = new SceneManager();
    MainMenu* mainMenu = new MainMenu();
    Stage1* stage1 = new Stage1();

    Globals::sceneManager->registerScene(mainMenu, 0);
    Globals::sceneManager->registerScene(stage1, 1);
    Globals::sceneManager->switchScene(0);

    std::cout << "Program started" << std::endl;
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        Scene* activeScene = Globals::sceneManager->getActiveScene();

        if (activeScene != nullptr) {
            activeScene->update(delta);
            activeScene->draw();
        }
    }
    CloseWindow();
    return 0;
}