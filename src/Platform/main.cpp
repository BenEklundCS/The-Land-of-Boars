#include <cstdlib>
#include "../../include/Platform/Engine.h"
#include <raylib.h>

/**
 * @brief Main function for "The Land of Boars."
 *
 * Initializes the game engine and starts the game. Exits gracefully on termination.
 *
 * @return Exit code for the operating system.
 */
int main() {
    try {
        // Create an instance of the game engine
        auto gameEngine = Engine();

        // Start the game

        gameEngine.StartGame();
        // Farewell message upon successful exit
        TraceLog(LOG_INFO, "You have triumphed or fallen in the Land of Boars. Until next time, hero!");
    } catch (const std::exception& ex) {
        // Handle unexpected exceptions
        TraceLog(LOG_ERROR, "An unexpected error occurred: ", ex.what());
        exit(EXIT_FAILURE);
    } catch (...) {
        // Catch any other errors
        TraceLog(LOG_ERROR, "An unknown error has occurred. Exiting...");
        exit(EXIT_FAILURE);
    }
}
