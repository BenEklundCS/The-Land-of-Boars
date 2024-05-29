//
// Created by ben on 5/28/24.
//

#include "GameManager.h"

void GameManager::LoadLevels() {
    auto levelOne = std::make_unique<LevelOne>();
    levels.push_back(std::move(levelOne));
}

void GameManager::StartGame() {

    Window* window = Window::GetInstance();

    LoadLevels();

    for (auto& level : levels) {
        level->StartLevel();
    }
}


