//
// Created by luke4 on 1/11/2025.
//

#include "../../../../include/Game/Events/Commands/EditorCommands.h"
#include "../../../../include/Game/Level/LevelLoader.h"

/**
 * @brief Executes the enter editor command on a gameState pointer to set its mode and transform the state of the renderer
 *
 * Calls the SetMode method on the gameState, and resets its camera. Also shows the cursor for editing purposes.
 */
void EnterEditorCommand::Execute(GameStateManager* gameState) {
    gameState->SetMode(MODE_EDITOR);
    gameState->InitCamera(); // reset the camera
    ShowCursor();
}

/**
 * @brief Executes the enter editor command on a gameState pointer to set its mode and transform the state of the renderer
 *
 * Calls the SetMode method on the gameState, and resets its camera. Also shows the cursor for editing purposes.
 */
void ExitEditorCommand::Execute(GameStateManager* gameState) {
    gameState->SetMode(MODE_GAME);
    gameState->InitCamera(); // reset the camera
    HideCursor();
}

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