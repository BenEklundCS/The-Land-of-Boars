//
// Created by ben on 6/10/24.
//

#ifndef PLATFORMER_INPUTMANAGER_H
#define PLATFORMER_INPUTMANAGER_H

#include "../Entities/Player/Player.h"
#include "../Events/Commands/PlayerCommands.h"


class EngineSettings;

struct PlayerCommands {
    JumpCommand* jumpCommand;
    LeftCommand* leftCommand;
    RightCommand* rightCommand;
    AttackCommand* attackCommand;
};

class InputManager {
private:
    PlayerCommands playerCommands;
    Player* player_;
    EngineSettings& settings_;
    void HandlePlayerInput();
    void HandleUIInput();
    static void HandleDebugInput();
public:
    explicit InputManager(Player* player, EngineSettings& settings)
    : player_(player), settings_(settings) {}
    void HandleUserInput();
};


#endif //PLATFORMER_INPUTMANAGER_H
