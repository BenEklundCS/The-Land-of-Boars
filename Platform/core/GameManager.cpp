//
// Created by ben on 5/28/24.
//

#include "../include/GameManager.h"
#include "../../Game/include/LevelOne.h"
#include "../include/Window.h"

// Load all the levels for the game
void GameManager::LoadLevels() {
    auto levelOne = std::make_unique<LevelOne>();
    // auto levelTwo =
    // auto LevelThree =
    // ...
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


