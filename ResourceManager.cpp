#include "ResourceManager.hpp"
#include <stdexcept>

// static members
std::unordered_map<std::string, Texture2D> ResourceManager::textures;
std::unordered_map<std::string, Sound> ResourceManager::sounds;
std::unordered_map<std::string, Music> ResourceManager::musics;

// Textures
Texture2D& ResourceManager::getTexture(const std::string& filename) {
    auto it = textures.find(filename);
    if (it != textures.end()) return it->second;

    Texture2D tex = LoadTexture(filename.c_str());
    if (tex.id == 0) throw std::runtime_error("Failed to load texture: " + filename);
    textures[filename] = tex;
    return textures[filename];
}

// Sounds
Sound& ResourceManager::getSound(const std::string& filename) {
    auto it = sounds.find(filename);
    if (it != sounds.end()) return it->second;

    Sound snd = LoadSound(filename.c_str());
    sounds[filename] = snd;
    return sounds[filename];
}

// Music
Music& ResourceManager::getMusic(const std::string& filename) {
    auto it = musics.find(filename);
    if (it != musics.end()) return it->second;

    Music music = LoadMusicStream(filename.c_str());
    musics[filename] = music;
    return musics[filename];
}

// Unload all
void ResourceManager::unloadAll() {
    for (auto& [_, tex] : textures) UnloadTexture(tex);
    textures.clear();

    for (auto& [_, snd] : sounds) UnloadSound(snd);
    sounds.clear();

    for (auto& [_, music] : musics) UnloadMusicStream(music);
    musics.clear();
}
