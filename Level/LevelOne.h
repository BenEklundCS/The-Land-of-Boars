//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_LEVELONE_H
#define PLATFORMER_LEVELONE_H

#include "Level.h"
#include "../Entities/Platform.h"

class LevelOne : public Level {
public:
    void Init() override;
    void Run() override;
};

#endif //PLATFORMER_LEVELONE_H
