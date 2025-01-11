//
// Created by luke4 on 1/11/2025.
//

#include "../../../include/Game/Level/LevelEditor.h"

#include "../../../include/Game/Management/GameStateManager.h"
#include "../../../include/Game/Management/TileManager.h"
#include "../../../include/Platform/GUI.h"

/**
* @brief Place a tile into the scene based on the user's selected tile.
*/
void LevelEditor::PlaceTile() {
    // Get the game state
    GameStateManager* gameState = GameStateManager::GetInstance();
    // Get the camera
    Camera2D camera = gameState->GetCamera();
    // Get the tileManager
    TileManager& tileManager = gameState->GetTileManager();

    // Logic for placing tile
    auto mousePos = GetMousePosition();
    auto worldPosition = GetScreenToWorld2D(mousePos, camera);
    auto tilePosition = tileManager.GetTileAt(worldPosition.x, worldPosition.y);
    int blockSelection = GUI::GetBlockSelection();
    TraceLog(LOG_INFO, "BLOCK SELECTION: %d", blockSelection);
    tileManager.SetTileAt(static_cast<int>(tilePosition.x), static_cast<int>(tilePosition.y), blockSelection); // Set the tile
    gameState->ReloadTiles();
}

/**
* @brief Print the location of a tile in the scene based on the user's selected tile.
*/
void LevelEditor::PrintTileLocation() {
    // Get the game state
    GameStateManager* gameState = GameStateManager::GetInstance();
    // Get the camera
    Camera2D camera = gameState->GetCamera();

    // Logic for getting a tile and printing the location
    TileManager& tileManager = gameState->GetTileManager();
    auto mousePos = GetMousePosition();
    auto worldPosition = GetScreenToWorld2D(mousePos, camera);
    auto tilePosition = tileManager.GetTileAt(worldPosition.x, worldPosition.y);
    TraceLog(LOG_INFO, "Tile at: %d, %d", static_cast<int>(tilePosition.x), static_cast<int>(tilePosition.y));
}
