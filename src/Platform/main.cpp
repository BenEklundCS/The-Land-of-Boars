#include <cstdlib>
#include "../../include/Platform/Engine.h"

int main() {
    // Create an instance of the game engine
    Engine gameEngine = Engine();
    // Start the game
    gameEngine.StartGame();
    // Exit the program successfully
    exit(EXIT_SUCCESS);

}
