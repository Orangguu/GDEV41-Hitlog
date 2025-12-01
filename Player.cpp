#include "Player.hpp"
#include "ResourceManager.hpp"
#include <cmath>
#include <iostream>

void Player::update(float dt) {
    Vector2 move = {0,0};
    // Movement input
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) move.y -= 1;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) move.y += 1;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) move.x -= 1;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) move.x += 1;

    // Normalize movement
    float mag = sqrt(move.x*move.x + move.y*move.y);
    Vector2 normMove = {0,0};
    if (mag > 0) normMove = {move.x/mag, move.y/mag};

    // Update dash cooldown
    dashCooldownTimer -= dt;
    if (dashCooldownTimer < 0.0f) dashCooldownTimer = 0.0f;

    // Start dash
    if (!is_dashing && dashCooldownTimer <= 0.0f && IsKeyPressed(KEY_SPACE)) {
        if (mag > 0) {
            is_dashing = true;
            dashTimer = dashDuration;
            dashDir = normMove;
            dashCooldownTimer = dashCooldown;
        }
    }

    // Apply movement
    if (is_dashing) {
        pos.x += dashDir.x * (dashDistance / dashDuration) * dt;
        pos.y += dashDir.y * (dashDistance / dashDuration) * dt;
        dashTimer -= dt;
        if (dashTimer <= 0.0f) is_dashing = false;
    } else {
        pos.x += normMove.x * speed * dt;
        pos.y += normMove.y * speed * dt;
    }

    // Clamp to screen bounds so player can't disappear off-screen
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    if (pos.x < radius) pos.x = radius;
    if (pos.y < radius) pos.y = radius;
    if (pos.x > screenW - radius) pos.x = screenW - radius;
    if (pos.y > screenH - radius) pos.y = screenH - radius;

    // Determine facing direction
    Vector2 dirToUse = is_dashing ? dashDir : normMove;
    if (dirToUse.x < 0 && dirToUse.y < 0) direction = UP_LEFT;
    else if (dirToUse.x > 0 && dirToUse.y < 0) direction = UP_RIGHT;
    else if (dirToUse.x < 0 && dirToUse.y > 0) direction = DOWN_LEFT;
    else if (dirToUse.x > 0 && dirToUse.y > 0) direction = DOWN_RIGHT;
    else if (dirToUse.x < 0) direction = LEFT;
    else if (dirToUse.x > 0) direction = RIGHT;
    else if (dirToUse.y < 0) direction = UP;
    else if (dirToUse.y > 0) direction = DOWN;

    // Update idle
    is_idle = (!is_dashing && normMove.x == 0 && normMove.y == 0);

    // Animation timer
    animTimer += dt;
    if (animTimer >= 1.0f / spriteFPS) {
        animTimer = 0;
        if (is_idle) {
            frameY = 1;
            frameX = (frameX == 0) ? 1 : 0; // Idle cycle
        } else {
            switch(direction) {
                case DOWN: case DOWN_RIGHT: case RIGHT:
                    frameY = 2;
                    break;
                case LEFT: case DOWN_LEFT:
                    frameY = 3;
                    break;
                case UP_LEFT: case UP:
                    frameY = 4; // row 5
                    break;
                case UP_RIGHT:
                    frameY = 5; // row 6
                    break;
            }
            frameX++;
            if(frameX == 5) frameX = 0;
        }
    }
}


void Player::draw() const {
    if (texturesLoaded) {
        Rectangle origFrame = { frameX * width, frameY * height, width, height };
        Rectangle dest = { pos.x, pos.y, width * spriteScale, height * spriteScale };
        DrawTexturePro(animTexture, origFrame, dest, {0, 0}, 0, WHITE);
    } else {
        // Fallback circle while loading
        if(is_dashing) DrawCircleV(pos, radius, ORANGE);
        else DrawCircleV(pos, radius, color);
    }
}
