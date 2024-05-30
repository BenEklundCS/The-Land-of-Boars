//
// Created by ben on 5/28/24.
//

#include "../include/GameManager.h"
#include "../../Game/include/Level/LevelOne.h"
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
        Scene* scene = level->GetScene();
        scene->InitCamera();
        RenderLevelScene(scene);
    }
}

// Take a Scene* as a parameter, initialize a renderer, and then render the scene
void GameManager::RenderLevelScene(Scene* scene) {
    renderer = Renderer();
    while (!WindowShouldClose() && !scene->IsLevelOver()) {
        scene->Update();        // Update the scene in every frame
        renderer.Draw(scene);   // Draw the scene using the renderer
    }
    delete scene;
}


