//
// Created by ben on 7/31/24.
//

#include "../../../../include/Game/Events/Commands/PlayerCommands.h"

void JumpCommand::Execute(Player *player) {
    player->Jump();
}

void LeftCommand::Execute(Player *player) {
    player->MoveLeft();
}

void RightCommand::Execute(Player *player) {
    player->MoveRight();
}

void AttackCommand::Execute(Player *player) {
    player->Attack();
}