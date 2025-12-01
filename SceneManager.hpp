#pragma once
#include "Scene.hpp"

#include <unordered_map>

class SceneManager {
    private:
        std::unordered_map<int, Scene*> allScenes;
        Scene* activeScene = nullptr;

    public:
        void registerScene(Scene* scene, int id);
        void unregisterScene(int id);
        void switchScene(int id);
        Scene* getActiveScene();
};