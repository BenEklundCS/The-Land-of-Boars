//
// Created by ben on 5/25/24.
//

#ifndef PLATFORMER_BOAR_H
#define PLATFORMER_BOAR_H

#include "Animation.h"
#include "Monster.h"


class Boar : public Monster {
private:
    Animation boarAnimation_;
public:
    Boar(float posX, float posY, float dimX, float dimY, MonsterState state);
    void Draw() override;
    void Update() override;
};


#endif //PLATFORMER_BOAR_H
