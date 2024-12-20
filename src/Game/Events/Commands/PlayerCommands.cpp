//
// Created by ben on 7/31/24.
//

#include "../../../../include/Game/Events/Commands/PlayerCommands.h"

/**
 * @brief Executes the jump command for the player.
 *
 * Calls the `Jump` method on the player, causing the player to jump.
 *
 * @param player Pointer to the player instance.
 */
void JumpCommand::Execute(Player *player) {
    // Make sure the player can jump before processing the jump command
    if (player->CanJump()) {
        player->Jump();
    }
}

/**
 * @brief Executes the move left command for the player.
 *
 * Calls the `MoveLeft` method on the player, causing the player to move left.
 *
 * @param player Pointer to the player instance.
 */
void LeftCommand::Execute(Player *player) {
    player->MoveLeft();
}

/**
 * @brief Executes the move right command for the player.
 *
 * Calls the `MoveRight` method on the player, causing the player to move right.
 *
 * @param player Pointer to the player instance.
 */
void RightCommand::Execute(Player *player) {
    player->MoveRight();
}

/**
 * @brief Executes the attack command for the player.
 *
 * Calls the `Attack` method on the player, causing the player to perform an attack.
 *
 * @param player Pointer to the player instance.
 */
void AttackCommand::Execute(Player *player) {
    player->Attack();
}