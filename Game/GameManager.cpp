//
// Created by ben on 5/28/24.
//

#include "GameManager.h"

// Load all the levels for the game
void GameManager::LoadLevels() {
    auto levelOne = std::make_unique<LevelOne>();
    levels.push_back(std::move(levelOne));
}

// Start the game by loading the levels, then playing them in sequence
void GameManager::StartGame() {
    // Get the window
    Window* window = Window::GetInstance();
    // Load all the levels
    LoadLevels();
    // Start each level
    for (auto& level : levels) {
        level->StartLevel();
    }
}


