//
// Created by ben on 7/31/24.
//

#ifndef PLATFORMER_PLAYERCOMMANDS_H
#define PLATFORMER_PLAYERCOMMANDS_H

#include "Command.h"
#include "../../Entities/Player/Player.h"

/**
 * @class JumpCommand
 * @brief Command class to execute the player's jump action.
 *
 * This class defines the static method `Execute`, which applies the
 * jump action to the player. It encapsulates the logic for triggering
 * a jump in a clean, reusable way.
 */
class JumpCommand : public Command {
public:
    /**
     * @brief Executes the jump action for the player.
     *
     * @param player Pointer to the `Player` object that will perform the jump.
     */
    static void Execute(Player* player);
};

/**
 * @class LeftCommand
 * @brief Command class to execute the player's move-left action.
 *
 * This class defines the static method `Execute`, which applies the
 * move-left action to the player. It encapsulates the logic for moving
 * the player left.
 */
class LeftCommand : public Command {
public:
    /**
     * @brief Executes the move-left action for the player.
     *
     * @param player Pointer to the `Player` object that will move left.
     */
    static void Execute(Player* player);
};

/**
 * @class RightCommand
 * @brief Command class to execute the player's move-right action.
 *
 * This class defines the static method `Execute`, which applies the
 * move-right action to the player. It encapsulates the logic for moving
 * the player right.
 */
class RightCommand : public Command {
public:
    /**
     * @brief Executes the move-right action for the player.
     *
     * @param player Pointer to the `Player` object that will move right.
     */
    static void Execute(Player* player);
};

/**
 * @class AttackCommand
 * @brief Command class to execute the player's attack action.
 *
 * This class defines the static method `Execute`, which applies the
 * attack action to the player. It encapsulates the logic for triggering
 * an attack in a clean, reusable way.
 */
class AttackCommand : public Command {
public:
    /**
     * @brief Executes the attack action for the player.
     *
     * @param player Pointer to the `Player` object that will perform the attack.
     */
    static void Execute(Player* player);
};

#endif //PLATFORMER_PLAYERCOMMANDS_H
