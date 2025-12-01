#include "SceneManager.hpp"

void SceneManager::registerScene(Scene* scene, int id) {
    allScenes.insert({id, scene});
}

void SceneManager::unregisterScene(int id) {
    if (auto iterator = allScenes.find(id); iterator != allScenes.end()) {
        allScenes.erase(iterator);
    }
}

void SceneManager::switchScene(int id) {
    if (activeScene != nullptr) {
        activeScene->exit();
    }
    activeScene = allScenes.at(id); // if scene doesn't exist, program fails
    activeScene->enter();
}

Scene* SceneManager::getActiveScene() {
    return activeScene;
}