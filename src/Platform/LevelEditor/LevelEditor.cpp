//
// Created by luke4 on 11/23/2024.
//

#include "../../../include/Platform/LevelEditor/LevelEditor.h"
#include <raylib.h>

#include "../../../include/Game/Management/GameStateManager.h"
#include "../../../include/Platform/LevelEditor/EditorInputManager.h"
#include "../../../include/Platform/Renderer.h"

LevelEditor::LevelEditor() {

}

void LevelEditor::EditLevel() {
    GameStateManager* gameState = GameStateManager::GetInstance();
    auto* inputManager = new EditorInputManager(this);
    EngineSettings* settings = Engine::GetSettings();
    Grid* grid = new Grid();
    while (!WindowShouldClose()) {
        // Process input
        inputManager->HandleEditorInput();
        // Draw the current frame without updating the game state
        BeginDrawing();
        ClearBackground(RAYWHITE); // Clear the screen with a white background
        Renderer::Draw(gameState, settings); // Draw the scene
        // Add any additional drawing code here
        grid->DrawGrid();
        EndDrawing();
    }
    free(gameState);
    free(inputManager);
    free(grid);
}

void LevelEditor::LoadLevel() {

}

void LevelEditor::SaveLevel() {

}

void LevelEditor::PlaceTile(Vector2 mousePosition) {

}

void LevelEditor::RemoveTile(Vector2 mousePosition) {

}





