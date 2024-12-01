//
// Created by luke4 on 11/24/2024.
//

#include "../../../include/Platform/LevelEditor/EditorInputManager.h"
#include <raylib.h>

EditorInputManager::EditorInputManager(LevelEditor* editor)
    : levelEditor_(editor) {}

void EditorInputManager::HandleEditorInput() {
    if (IsKeyPressed(KEY_S)) {
        TraceLog(LOG_INFO, "Save level triggered.");
        levelEditor_->SaveLevel();
    }

    if (IsKeyPressed(KEY_L)) {
        TraceLog(LOG_INFO, "Load level triggered.");
        levelEditor_->LoadLevel();
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePosition = GetMousePosition();
        levelEditor_->PlaceTile(mousePosition);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector2 mousePosition = GetMousePosition();
        levelEditor_->RemoveTile(mousePosition);
    }

    // Add more editor-specific input handling as needed
}

