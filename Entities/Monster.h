//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_MONSTER_H
#define PLATFORMER_MONSTER_H

#include "GameObject.h"


class Monster : public GameObject {
private:

public:
    void Draw() override;
    void Update() override;
};


#endif //PLATFORMER_MONSTER_H
