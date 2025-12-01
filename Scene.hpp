#pragma once

class Scene {
    public:
        virtual void enter() = 0;
        virtual void update(float delta) = 0;
        virtual void draw() = 0;
        virtual void exit() = 0;
};