//
// Created by ben on 5/17/24.
//

#include "Monster.h"

Monster::Monster(float pos_x, float pos_y, float dim_x, float dim_y, MonsterState state) {
    this->position_.x = pos_x;
    this->position_.y = pos_y;
    this->dimensions_.x = dim_x;
    this->dimensions_.y = dim_y;
    this->state_ = state;
    this->initialPosition_ = position_;
    this->movingRight_ = false;
}

void Monster::Update() {
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
}

// Draw a rectangle for now
void Monster::Draw() {
    DrawRectangle((int)position_.x, (int)position_.y, (int)dimensions_.x, (int)dimensions_.y, RED);
}

// Monster implements its own collision with the player
// Will deal damage to the player, or end the game
void Monster::CollideWithPlayer(Player* player) {
    if (CheckCollisionRecs(player->GetRect(), GetRect())) {
        TraceLog(LOG_INFO, "Touched");
    }
}