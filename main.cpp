#include "raylib.h"
#include "Bullet.hpp"
#include "Player.hpp"

Bullet bullet;
Player player;
const int FPS = 60;
float bulletCooldown = 0.5f;
float bulletTimer = bulletCooldown;

int main(){

    Vector2 mousePos;
    SetTargetFPS(FPS);
    InitWindow(1200, 900, "Pew Pew Pew");

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        bulletTimer += dt;

        // Shooting
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && bulletTimer >= bulletCooldown) {
            Vector2 startPos = { player.pos.x + player.width * 2.5f, player.pos.y + player.height * 2.5f }; // adjust to player center
            Vector2 mousePos = GetMousePosition();
            bullet.fire(startPos, mousePos);
            bulletTimer = 0;
        }

        // Update and draw bullet
        bullet.update(dt);
        player.update(dt);
        BeginDrawing();
        ClearBackground(BLACK);
        player.draw();
        bullet.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}