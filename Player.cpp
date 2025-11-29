#include "Player.hpp"
#include <cmath>

void Player::update(float dt) {
    Vector2 move = {0, 0};

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) move.y -= 1;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) move.y += 1;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) move.x -= 1;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) move.x += 1;

    // Velocity normalization
    float mag = sqrt(move.x * move.x + move.y * move.y);
    if (mag > 0) {
        move.x /= mag;
        move.y /= mag;
    }

    pos.x += move.x * speed * dt;
    pos.y += move.y * speed * dt;

    // Update direction
    if (move.x < 0 && move.y < 0) direction = UP_LEFT;
    else if (move.x > 0 && move.y < 0) direction = UP_RIGHT;
    else if (move.x < 0 && move.y > 0) direction = DOWN_LEFT;
    else if (move.x > 0 && move.y > 0) direction = DOWN_RIGHT;
    else if (move.x < 0) direction = LEFT;
    else if (move.x > 0) direction = RIGHT;
    else if (move.y < 0) direction = UP;
    else if (move.y > 0) direction = DOWN;

    is_idle = (move.x == 0 && move.y == 0);

    // Animation timer
    animTimer += dt;
    if (animTimer >= 1.0f / spriteFPS) {
        animTimer = 0;

        if (is_attacking) {
            frameX++;
            if (frameX > 2) {
                frameX = 0;
                is_attacking = false;
            }
        } else if (is_idle) {
            frameX = (frameX == 0) ? 1 : 0; // Idle cycle
        } else {
            frameX = (frameX == 2) ? 3 : 2; // Walk cycle
        }
    }

    // Map direction to frameY
    frameY = static_cast<int>(direction);
}

void Player::draw() const {
    /*
    Texture currentTexture = is_attacking ? attackTexture : walkTexture;
    Rectangle origFrame = { frameX * width, frameY * height, width, height };
    Rectangle dest = { pos.x, pos.y, width * spriteScale, height * spriteScale };
    DrawTexturePro(currentTexture, origFrame, dest, {0, 0}, 0, WHITE);
    */
    DrawCircleV(pos, radius, color);
}
