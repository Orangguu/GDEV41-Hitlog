#include "Stage1.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

void Stage1::update(float delta) {
    bulletTimer += delta;

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && bulletTimer >= bulletCooldown) {
        Vector2 startPos = { player.pos.x + player.width * 2.5f, player.pos.y + player.height * 2.5f }; // adjust to player center
        Vector2 mousePos = GetMousePosition();
        bullet.fire(startPos, mousePos);
        bulletTimer = 0;
    }

    bullet.update(delta);
    player.update(delta);
}

void Stage1::draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    bullet.draw();
    player.draw();
    EndDrawing();
}

void Stage1::enter() {
}

void Stage1::exit() {
}