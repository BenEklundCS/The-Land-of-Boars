//
// Created by ben on 7/31/24.
//

#ifndef PLATFORMER_PLAYERCOMMANDS_H
#define PLATFORMER_PLAYERCOMMANDS_H

#include "Command.h"
#include "../../Entities/Player/Player.h"

class JumpCommand : public Command {
public:
    static void Execute(Player* player);
};

class LeftCommand : public Command {
public:
    static void Execute(Player* player);
};

class RightCommand : public Command {
public:
    static void Execute(Player* player);
};

class AttackCommand : public Command {
public:
    static void Execute(Player* player);
};

#endif //PLATFORMER_PLAYERCOMMANDS_H


