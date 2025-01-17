//
// Created by luke4 on 1/11/2025.
//

#ifndef EDITORCOMMANDS_H
#define EDITORCOMMANDS_H

#include "../../Management/GameStateManager.h"

#include "../../Level/LevelEditor.h"

/**
 * @class EnterEditorCommand
 * @brief Provides a static utility method for entering the Level Editor
 */
class EnterEditorCommand {
public:
    static void Execute(GameStateManager* gameState); // Static method for entering the editor state
};

/**
 * @class ExitEditorCommand
 * @brief Provides a static utility method for entering the Level Editor
 */
class ExitEditorCommand {
public:
    static void Execute(GameStateManager* gameState); // Static method exiting the editor state
};

/**
 * @class PlaceTileCommand
 * @brief Provides static utility methods for placing tiles in the editor.
 */
class PlaceTileCommand {
public:
    static void Execute(); // Static method for placing tiles
};

/**
 * @class PrintTileCommand
 * @brief Provides static utility methods for printing tile information.
 */
class PrintTileCommand {
public:
    static void Execute(); // Static method for printing tile info
};

/**
 * @class SaveLevelCommand
 * @brief Provides static utility methods for saving levels.
 */
class SaveLevelCommand {
public:
    static void Execute(); // Static method for saving levels
};

/**
 * @class LoadLevelCommand
 * @brief Provides static utility methods for loading levels.
 */
class LoadLevelCommand {
public:
    static void Execute(); // Static method for loading levels
};

#endif // EDITORCOMMANDS_H
