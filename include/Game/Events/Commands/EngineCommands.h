//
// Created by ben on 1/14/25.
//

#ifndef THE_LAND_OF_BOARS_ENGINECOMMANDS_H
#define THE_LAND_OF_BOARS_ENGINECOMMANDS_H

/**
 * @brief Executes the command to stop the game.
 *
 * This method calls the `StopGame` function of the `Engine` class,
 * which sets the flag to exit the game loop and terminate the game.
 */
class StopGameCommand {
public:
    static void Execute();
};

#endif //THE_LAND_OF_BOARS_ENGINECOMMANDS_H
