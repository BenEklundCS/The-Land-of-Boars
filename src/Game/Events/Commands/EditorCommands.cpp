//
// Created by luke4 on 1/11/2025.
//

#include "../../../../include/Game/Events/Commands/EditorCommands.h"
#include "../../../../include/Game/Level/LevelLoader.h"
#include "../../../../include/Game/Management/GameStateManager.h"

/**
 * @brief Executes the place tile command in the level editor.
 *
 * Calls the `PlaceTile` method on the `LevelEditor`, placing a tile at the current location.
 */
void PlaceTileCommand::Execute() {
    LevelEditor::PlaceTile();
}

/**
 * @brief Executes the print tile command in the level editor.
 *
 * Calls the `PrintTileLocation` method on the `LevelEditor`, printing the current tile location.
 */
void PrintTileCommand::Execute() {
    LevelEditor::PrintTileLocation();
}

/**
 * @brief Executes the save level command in the level editor.
 *
 * Calls the `SaveLevel` method on the `LevelLoader`, saving the current level to a file.
 */
void SaveLevelCommand::Execute() {
    TraceLog(LOG_INFO, "Saving level...");
    LevelLoader::SaveLevel(GameStateManager::GetInstance()->GetTileManager().GetTiles(), "../Levels/myLevel.txt");
}

/**
 * @brief Executes the load level command in the level editor.
 *
 * Calls the `LoadLevel` method on the `LevelLoader`, loading a level from a file.
 */
void LoadLevelCommand::Execute() {
    TraceLog(LOG_INFO, "Loading level...");
}