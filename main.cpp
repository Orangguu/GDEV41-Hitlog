#include "raylib.h"
#include "Stage1.hpp"

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 900;
const int FPS = 60;

int main(){
    SetTargetFPS(FPS);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pew Pew Pew");

    Stage1 stage1(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        stage1.update(delta);

        BeginDrawing();
        stage1.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}