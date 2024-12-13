//
// Created by ben on 5/17/24.
//


#include "../../../../include/Game/Entities/Monsters/Monster.h"
#include "../../../../include/Game/Management/GameStateManager.h"

/**
 * @brief Constructs a Monster object with specified position, dimensions, and state.
 *
 * The Monster is initialized with default values for health, velocity, and movement direction.
 *
 * @param pos_x The x-coordinate of the Monster's position.
 * @param pos_y The y-coordinate of the Monster's position.
 * @param dim_x The width of the Monster.
 * @param dim_y The height of the Monster.
 * @param state The initial state of the Monster.
 */
Monster::Monster(const float pos_x, const float pos_y, const float dim_x, const float dim_y, const MonsterState state) : GameObject(MONSTER) {
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

/**
 * @brief Updates the Monster's position and applies gravity.
 */
void Monster::Update() {
    MoveMonster();
    float deltaTime = GetFrameTime();
    ApplyGravity(deltaTime);
    GameObject::Update();
}

/**
 * @brief Draws the Monster to the screen.
 *
 * Currently, the Monster is rendered as a simple rectangle.
 */
void Monster::Draw() {
    DrawRectangle((int)position_.x, (int)position_.y, (int)dimensions_.x, (int)dimensions_.y, color_);
}

#pragma endregion

#pragma region object collisions

/**
 * @brief Handles collisions between the Monster and a Player.
 *
 * If the Monster collides with the Player, it deals damage or triggers a game-ending event.
 *
 * @param player Pointer to the Player object.
 */
void Monster::CollideWithPlayer(Player* player) {
    if (CheckCollisionRecs(player->GetRect(), GetRect())) {
        player->HitPlayer();
    }
}

#pragma endregion

#pragma region update methods

/**
 * @brief Moves the Monster based on its state.
 *
 * The Monster can pace back and forth, move towards a player while flying, or follow a default movement behavior.
 */
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
    else if (this->state_ == MOVE_TO_FLYING) {
        Vector2 player1_position = GameStateManager::GetInstance()->GetPlayers().at(0)->GetPosition();
        if (player1_position.x > position_.x) {
            position_.x += MONSTER_SPEED * 2;
            movingRight_ = true;
        }
        else {
            position_.x -= MONSTER_SPEED * 2;
            movingRight_ = false;
        }
        if (player1_position.y > position_.y) {
            position_.y += MONSTER_SPEED * 2;
        }
        else {
            position_.y -= MONSTER_SPEED * 2;
        }
    }
    // Default
    else {
        // Otherwise just update the position based on the speed
        MoveDefault();
    }
}

/**
 * @brief Handles the default movement behavior for the Monster.
 */
void Monster::MoveDefault() {
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

/**
 * @brief Applies gravity to the Monster.
 *
 * @param deltaTime The time elapsed since the last frame.
 */
void Monster::ApplyGravity(const float deltaTime) {
    if (velocity_.y <= MAX_VELOCITY) {
        velocity_.y += GRAVITY * deltaTime;
    }
}

/**
 * @brief Retrieves the Monster's current health.
 *
 * @return The health of the Monster.
 */
int Monster::GetHealth() const {
    return this->hp_;
}

/**
 * @brief Sets the Monster's health to a specified value.
 *
 * @param hp The new health value for the Monster.
 */
void Monster::SetHealth(const int hp) {
    this->hp_ = hp;
}

/**
 * @brief Reduces the Monster's health by the specified damage amount.
 *
 * Also triggers a flashing effect to indicate the Monster has been hit.
 *
 * @param damage The amount of damage dealt to the Monster.
 */
void Monster::HitMonster(const int damage) {
    GameObject::ToggleFlashing();
    SetHealth(GetHealth() - damage);
}

#pragma endregion