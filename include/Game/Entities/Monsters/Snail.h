//
// Created by ben on 11/1/24.
//

#ifndef THE_LAND_OF_BOARS_SNAIL_H
#define THE_LAND_OF_BOARS_SNAIL_H

#include "Monster.h"
#include "../../Sprites/Animation.h"

#define SNAIL_MAX_HEALTH 2

class Snail : public Monster {
private:
    std::unique_ptr<Animation> snailAnimation_;
    void Died();
    void BeginDeathAnimation();
    void AnimateSnail();
public:
    Snail(float posX, float posY, float dimX, float dimY, MonsterState state);
    void Draw() override;
    void Update() override;
    void HitMonster(int damage) override;
};

#endif //THE_LAND_OF_BOARS_SNAIL_H
