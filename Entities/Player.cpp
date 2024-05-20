//
// Created by ben on 5/17/24.
//

#include "Player.h"
#include "../Sprites/TextureManager.h"

Player::Player() : playerAnimation_(TextureManager::GetInstance()->GetTexture(PLAYER_IDLE_TEXTURE), PLAYER_IDLE_FRAMES, 0.2f) {
    this->position_ = {100, 100};
    this->dimensions_ = {PLAYER_LENGTH, PLAYER_LENGTH};
    this->color_ = BLUE;
    state = IDLE;
    last_state = IDLE;
}

void Player::Draw() {
    // Get the playerTexture sheet and currentRect from the Animation object
    Texture2D playerTexture = playerAnimation_.GetTexture();
    Rectangle currentRect = playerAnimation_.GetCurrentRect();
    // Draw the player utilizing the currently loaded playerTexture, and rect position
    DrawTexturePro(playerTexture, currentRect, GetRect(), Vector2{0, 0}, 0, WHITE);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

void Player::Update() {
    // Handle Player Input
    HandlePlayerInput();
    // Move the player based on their velocity and position
    MovePlayer();
    // Check to see if we need to update the displayed animation
    AnimatePlayer();
    // Call Animate to get the next rect
    playerAnimation_.Animate();
    // Handle the updating of the player's animation state
    last_state = state;
    if (velocity_.x == 0 && velocity_.y == 0) {
        state = IDLE;
    }
}

void Player::MovePlayer() {

    float deltaTime = GetFrameTime();
    const int minVelocity = 1;

    // X axis movement
    position_.x += velocity_.x; // Update the X position based on the X-axis velocity

    // Handle friction / velocity reduction over time
    if (velocity_.x > minVelocity) {
        velocity_.x -= FRICTION * deltaTime; // friction
    }
    else if (velocity_.x < -minVelocity) {
        velocity_.x += FRICTION * deltaTime; // friction
    }
    else {
        velocity_.x = 0;
    }

    // Gravity
    velocity_.y += GRAVITY * deltaTime;
    // Apply vertical velocity
    position_.y += velocity_.y;
}

void Player::HandlePlayerInput() {

    float deltaTime = GetFrameTime();

    float maxXVelocity = 25;

    const float jumpPower = 7;

    if (IsKeyDown(KEY_A)) { // move left
        // If the player is not also jumping, we'll display the RUNNING animation
        if (velocity_.y == 0) {
            state = RUNNING;
        }
        // Flip the animation across the X axis - feed the "moving right" boolean value
        playerAnimation_.FlipX(false); // flip x, not moving right
        // Set the player's X velocity
        if (velocity_.x >= -maxXVelocity) {
            velocity_.x -= PLAYER_SPEED * deltaTime;
        }
    }
    if (IsKeyDown(KEY_D)) { // move right
        // If the player is not also jumping, we'll display the RUNNING animation
        if (velocity_.y == 0) {
            state = RUNNING;
        }
        // Flip the animation across the X axis - feed the "moving right" boolean value
        playerAnimation_.FlipX(true); // flip x, moving right
        // Set the player's X velocity
        if (velocity_.x <= maxXVelocity) {
            velocity_.x += PLAYER_SPEED * deltaTime;
        }
    }
    // Handle jumping and jump animation state management
    if ((IsKeyPressed(KEY_SPACE) && velocity_.y == 0)) { // jump
        state = JUMPING;
        velocity_.y -= PLAYER_SPEED * jumpPower * deltaTime;
    }
}

void Player::PlatformCollision(GameObject* obj) {
    // Stop the player's downward movement
    velocity_ = Vector2{velocity_.x, 0};
    // Set the player's position to be just above the object
    position_ = Vector2{position_.x, obj->GetPosition().y - dimensions_.y};
}

void Player::AnimatePlayer() {
    // Check to see if we need to load the IDLE animation
    TextureManager* textureManager = TextureManager::GetInstance();
    if (state == IDLE && last_state != IDLE) {
        TraceLog(LOG_INFO, "IDLE");
        playerAnimation_ = Animation(textureManager->GetTexture(PLAYER_IDLE_TEXTURE), PLAYER_IDLE_FRAMES, 0.2f);
    }
    // Check to see if we need to load the RUNNING animation
    else if (state == RUNNING && last_state != RUNNING) {
        TraceLog(LOG_INFO, "RUNNING");
        playerAnimation_ = Animation(textureManager->GetTexture(PLAYER_RUNNING_TEXTURE), PLAYER_RUNNING_FRAMES, 0.2f);
    }
        // Check to see if we need to load the JUMPING animation
    else if (state == JUMPING && last_state != JUMPING) {
        TraceLog(LOG_INFO, "JUMPING");
        playerAnimation_ = Animation(textureManager->GetTexture(PLAYER_JUMPING_TEXTURE), PLAYER_JUMPING_FRAMES, 0.075f);
    }
}

