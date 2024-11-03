//
// Created by ben on 5/17/24.
//


#include "../../../../include/Game/Entities/Monsters/Monster.h"

Monster::Monster(float pos_x, float pos_y, float dim_x, float dim_y, MonsterState state) : GameObject(MONSTER) {
    this->position_.x = pos_x;
    this->position_.y = pos_y;
    this->dimensions_.x = dim_x;
    this->dimensions_.y = dim_y;

    this->state_ = state;
    this->initialPosition_ = position_;
    this->movingRight_ = false;
    this->velocity_ = Vector2{0, 0};
    this->hp_ = 3;
}

#pragma region render methods

void Monster::Update() {
    MoveMonster();
    float deltaTime = GetFrameTime();
    ApplyGravity(deltaTime);
    GameObject::Update();
}

// Draw a rectangle for now
void Monster::Draw() {
    DrawRectangle((int)position_.x, (int)position_.y, (int)dimensions_.x, (int)dimensions_.y, color_);
}

#pragma endregion

#pragma region object collisions

// Monster implements its own collision with the player
// Will deal damage to the player, or end the game
void Monster::CollideWithPlayer(Player* player) {
    if (CheckCollisionRecs(player->GetRect(), GetRect())) {
        player->HitPlayer();
    }
}

#pragma endregion

#pragma region update methods

void Monster::MoveMonster() {
    // If the monster is pacing, calculate boundaries and move between them
    if (this->state_ == PACING) {
        float leftBound = initialPosition_.x - PACING_WINDOW;
        float rightBound = initialPosition_.x + PACING_WINDOW;
        // Toggle movingRight_ based on the position vs boundaries
        if (position_.x <= leftBound && !movingRight_) {
            movingRight_ = true;
        }
        else if (position_.x >= rightBound && movingRight_) {
            movingRight_ = false;
        }
    }
    // Otherwise just update the position based on the speed
    if (movingRight_) {
        position_.x += MONSTER_SPEED;
    }
    else {
        position_.x -= MONSTER_SPEED;
    }
    // Move Y axis
    position_.y += velocity_.y;
}

void Monster::ApplyGravity(float deltaTime) {
    if (velocity_.y <= MAX_VELOCITY) {
        velocity_.y += GRAVITY * deltaTime;
    }
}

int Monster::GetHealth() const {
    return this->hp_;
}

void Monster::SetHealth(int hp) {
    this->hp_ = hp;
}

void Monster::HitMonster(int damage) {
    GameObject::ToggleFlashing();
    SetHealth(GetHealth() - damage);
}

#pragma endregion