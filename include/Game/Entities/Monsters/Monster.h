//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_MONSTER_H
#define PLATFORMER_MONSTER_H

#include "../GameObject.h"
#include "../Player/Player.h"

#define PACING_WINDOW (800 * WINDOW_SCALE_FACTOR_X) // Scale pacing window to the screen size
#define MONSTER_SPEED (3 * WINDOW_SCALE_FACTOR_X)

// Definition for MonsterState
enum MonsterState {
    PACING,
    MOVE_TO_GROUNDED,
    MOVE_TO_FLYING,
    DYING,
    DEFAULT
};

class Monster : public GameObject, public Subject {
private:
    // Current monster state
    Vector2 initialPosition_{}; // The monster's initialPosition vector
protected:
    int hp_;
    MonsterState state_;
public:
    GameObjectType type_ = MONSTER; // Monster's GameObjectType
    Monster(float pos_x, float pos_y, float dim_x, float dim_y, MonsterState state);
    void Draw() override; // Draw the monster
    void Update() override; // Update the monster
    void ApplyGravity(float deltaTime); // Apply gravity to the monster
    void MoveMonster(); // Move the monster based on its velocity
    void CollideWithPlayer(Player* player) override; // Handle player collisions
    [[nodiscard]] int GetHealth() const;
    void SetHealth(int hp);
    virtual void HitMonster(int damage);
    void MoveDefault();
};

#endif //PLATFORMER_MONSTER_H