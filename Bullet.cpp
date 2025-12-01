#include "Bullet.hpp"
#include <cmath>

Texture2D Bullet::defaultTexture = {0};
void Bullet::fire(Vector2 startPos, Vector2 target) {
    pos = startPos;

    // Compute normalized direction
    dir.x = target.x - startPos.x;
    dir.y = target.y - startPos.y;
    float len = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len > 0) {
        dir.x /= len;
        dir.y /= len;
    }
    
    texture = defaultTexture;
    texturesLoaded = true;
    rotation = static_cast<float>(rand() % 360);
    active = true;
}

void Bullet::update(float dt) {
    if (!active) return; // only update if active

    pos.x += dir.x * speed * dt;
    pos.y += dir.y * speed * dt;

    // Deactivate if out of screen bounds
    if (pos.x < 0 || pos.x > GetScreenWidth() ||
        pos.y < 0 || pos.y > GetScreenHeight()) {
        active = false;
    }
}

void Bullet::draw() const {
    if (!active) return; // only draw if active

    if(texturesLoaded){
        Rectangle origFrame = { frameSize.x, frameSize.y, frameSize.x, frameSize.y, };
        Rectangle dest = { pos.x, pos.y, frameSize.x * spriteScale, frameSize.y * spriteScale };
        Vector2 origin = { radius, radius }; // rotate around center
        DrawTexturePro(texture, origFrame, dest, origin, rotation, WHITE);
    } else DrawCircleV(pos, radius, Color{240, 216, 225, 255});
}
