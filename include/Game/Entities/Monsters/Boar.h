//
// Created by ben on 5/25/24.
//

#ifndef PLATFORMER_BOAR_H
#define PLATFORMER_BOAR_H

#include "Monster.h"
#include "../../Sprites/Animation.h"

#define BOAR_MAX_HEALTH 3

class Boar : public Monster {
private:
    Animation boarAnimation_; // Boar animation
    void MaybeOink();
    float timeSinceLastOink_ = 0.0f; // Add this member variable
    float nextOinkTime_ = 0.0f; // Time until the next oink
public:
    Boar(float posX, float posY, float dimX, float dimY, MonsterState state);
    void Draw() override; // Draw the boar
    void Update() override; // Update the boar
    void HitMonster(int damage) override; // override the HitMonster function
    void DeathAnimation();
};


#endif //PLATFORMER_BOAR_H
