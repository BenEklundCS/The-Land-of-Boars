//
// Created by ben on 10/8/24.
//

#ifndef THE_LAND_OF_BOARS_BEE_H
#define THE_LAND_OF_BOARS_BEE_H

#include "Monster.h"
#include "../../Sprites/Animation.h"

#define BEE_MAX_HEALTH 2

class Bee : public Monster {
private:
    std::unique_ptr<Animation> beeAnimation_; // Boar animation
    void Died();
    void AnimateBee();
public:
    Bee(float posX, float posY, float dimX, float dimY, MonsterState state);
    void Draw() override; // Draw the boar
    void Update() override; // Update the boar
    void HitMonster(int damage) override; // override the HitMonster function
};

#endif //THE_LAND_OF_BOARS_BEE_H
