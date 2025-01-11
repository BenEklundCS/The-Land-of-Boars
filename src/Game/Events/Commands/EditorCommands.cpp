//
// Created by luke4 on 1/11/2025.
//

#include "../../../../include/Game/Events/Commands/EditorCommands.h"
#include "../../../../include/Game/Level/LevelLoader.h"
#include "../../../../include/Game/Management/GameStateManager.h"

void PlaceTileCommand::Execute() {
    LevelEditor::PlaceTile();
}

void PrintTileCommand::Execute() {
    LevelEditor::PrintTileLocation();
}

void SaveLevelCommand::Execute() {
    TraceLog(LOG_INFO, "Saving level...");
    LevelLoader::SaveLevel(GameStateManager::GetInstance()->GetTileManager().GetTiles(), "../Levels/myLevel.txt");
}

void LoadLevelCommand::Execute() {
    TraceLog(LOG_INFO, "Loading level...");
}



