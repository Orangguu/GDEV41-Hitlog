#pragma once
#include "raylib.h"
#include <string>
#include <unordered_map>

class ResourceManager {
public:
    // Textures
    static Texture2D& getTexture(const std::string& filename);

    // Sounds
    static Sound& getSound(const std::string& filename);

    // Music
    static Music& getMusic(const std::string& filename);

    // Unload everything
    static void unloadAll();

private:
    static std::unordered_map<std::string, Texture2D> textures;
    static std::unordered_map<std::string, Sound> sounds;
    static std::unordered_map<std::string, Music> musics;
};
