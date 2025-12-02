#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "LeaderBoard.hpp"
#include "globals.hpp"
#include "ResourceManager.hpp"

struct PlayerScore {
    std::string name;
    int score;
};

// Member variable in LeaderBoard.hpp
std::vector<PlayerScore> scores;

void LeaderBoard::enter() {
    // Load scores from file
    scores.clear();
    std::ifstream file("scores.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name;
            int score;
            if (iss >> name >> score) {
                scores.push_back({name, score});
            }
        }
        file.close();
    }

    // Sort scores descending
    std::sort(scores.begin(), scores.end(), [](const PlayerScore& a, const PlayerScore& b) {
        return a.score > b.score;
    });

    bgMusic = ResourceManager::getSound("./assets/music/music_leaderboard.wav");
    if (Globals::music_enabled) {
        PlaySound(bgMusic);
    }
}

void LeaderBoard::update(float delta){
    if (Globals::music_enabled && !IsSoundPlaying(bgMusic)) {
        PlaySound(bgMusic);
    }
}

void LeaderBoard::draw() {
    BeginDrawing();

    if (bgTexture.id != 0)
        DrawTexture(bgTexture, 0, 0, WHITE);
    else
        ClearBackground(Color{20, 20, 30, 255});

    // Draw big "Leaderboard" title
    ui.text(0, "LEADERBOARD", {100, 50, 1200, 100}, 96, Color{255, 215, 0, 255}); 

    // x, y, width, height, font size, color
    // Display top scores
    float y = 200.0f; // starting y position
    int rank = 1;
    for (const auto& ps : scores) {
        std::string text = std::to_string(rank) + ". " + ps.name + " - " + std::to_string(ps.score);
        ui.text(10 + rank, text, {100, y, 400, 50}, 36, WHITE);
        y += 60;
        rank++;
        if (rank > 10) break; // show only top 10
    }

    // Buttons
    if (ui.button(1, "Try Again", {1060, 580, 300, 70}, 56)) {
        Globals::sceneManager->switchScene(1); // restart Stage 1
    }

    if (ui.button(2, "Main Menu", {1060, 710, 300, 70}, 56)) {
        Globals::sceneManager->switchScene(0); // go to main menu
    }

    EndDrawing();
}

void LeaderBoard::exit(){
    ResourceManager::unloadAll();
}
