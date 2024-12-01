//
// Created by ben on 6/10/24.
//

#ifndef PLATFORMER_INPUTMANAGER_H
#define PLATFORMER_INPUTMANAGER_H

#include "../Entities/Player/Player.h"
#include "../../Platform/LevelEditor/LevelEditor.h"
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
    PlayerCommands playerCommands{};
    Player* player_;
    LevelEditor* levelEditor_;
    EngineSettings& settings_;
    void HandlePlayerInput() const;
    void HandleUIInput() const;
    void HandleDebugInput() const;
public:
    explicit InputManager(Player* player, EngineSettings& settings, LevelEditor* levelEditor)
    : player_(player), settings_(settings), levelEditor_(levelEditor) {}
    void HandleUserInput() const;
};


#endif //PLATFORMER_INPUTMANAGER_H
