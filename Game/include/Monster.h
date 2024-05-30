//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_MONSTER_H
#define PLATFORMER_MONSTER_H

#include "GameObject.h"
#include "../src/Entities/Player/Player.h"
#include "PhysicsConstants.h"

#define PACING_WINDOW 800
#define MONSTER_SPEED 3

enum MonsterState {
    PACING,
    DEFAULT
};

class Monster : public GameObject {
private:
    MonsterState state_;
    Vector2 initialPosition_{};
    Vector2 velocity_{};
protected:
    bool movingRight_;
public:
    GameObjectType type_;
    Monster(float pos_x, float pos_y, float dim_x, float dim_y, MonsterState state);
    void Draw() override;
    void Update() override;
    void ApplyGravity(float deltaTime);
    void MoveMonster();
    void PlatformCollision(GameObject* obj);
    void CollideWithPlayer(Player* player) override;
};


#endif //PLATFORMER_MONSTER_H