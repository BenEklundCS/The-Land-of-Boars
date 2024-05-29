//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_LEVELONE_H
#define PLATFORMER_LEVELONE_H

#include "Level.h"
#include "../Entities/Objects/Platform.h"
#include "../Entities/Monsters/Boar.h"

class LevelOne : public Level {
private:
    bool gameOver_;
public:
    void StartLevel() override;
    void GameOver();
};

#endif //PLATFORMER_LEVELONE_H
