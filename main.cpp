#include "raylib.h"
#include "globals.hpp"
#include "Stage1.hpp"
#include "MainMenu.hpp"
#include "SceneManager.hpp"
#include "GameOver.hpp"
#include "Leaderboard.hpp"
#include <iostream>

const int FPS = 60;

int main() {
    SetTargetFPS(FPS);
    InitWindow(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT, "Hitlog");
    InitAudioDevice();

    Globals::sceneManager = new SceneManager();
    MainMenu* mainMenu = new MainMenu();
    Stage1* stage1 = new Stage1();
    GameOver* gameOver = new GameOver();
    LeaderBoard* leaderBoard = new LeaderBoard();

    stage1->setGameOverScene(gameOver);

    Globals::sceneManager->registerScene(mainMenu, 0);
    Globals::sceneManager->registerScene(stage1, 1);
    Globals::sceneManager->registerScene(gameOver, 2);
    Globals::sceneManager->registerScene(leaderBoard, 3);
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
    CloseAudioDevice();
    CloseWindow();
    return 0;
}