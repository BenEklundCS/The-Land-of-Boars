//
// Created by ben on 7/31/24.
//

#include "../../../../include/Game/Events/Commands/PlayerCommands.h"

void JumpCommand::execute(Player *player) {
    player->Jump();
}

void LeftCommand::execute(Player *player) {
    player->MoveLeft();
}

void RightCommand::execute(Player *player) {
    player->MoveRight();
}

void AttackCommand::execute(Player *player) {
    player->Attack();
}