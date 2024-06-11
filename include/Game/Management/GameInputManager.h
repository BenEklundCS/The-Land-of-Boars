//
// Created by ben on 6/10/24.
//

#ifndef PLATFORMER_GAMEINPUTMANAGER_H
#define PLATFORMER_GAMEINPUTMANAGER_H

#include "../Entities/Player/Player.h"

class GameInputManager {
private:
    Player* player_;
    void HandlePlayerInput();
    void HandleUIInput();
    void HandleDebugInput();
public:
    explicit GameInputManager(Player* player) {
        player_ = player;
    }
    void HandleUserInput();
};


#endif //PLATFORMER_GAMEINPUTMANAGER_H
