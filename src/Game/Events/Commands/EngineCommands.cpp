//
// Created by ben on 1/14/25.
//

#include "../../../../include/Game/Events/Commands/EngineCommands.h"
#include "../../../../include/Platform/Engine.h"


/**
 * @brief Executes the command to stop the game.
 *
 * This method calls the `StopGame` function of the `Engine` class,
 * which sets the flag to exit the game loop and terminate the game.
 */
void StopGameCommand::Execute() {
    Engine::StopGame();
}
