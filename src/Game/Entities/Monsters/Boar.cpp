//
// Created by ben on 5/25/24.
//

#include "../../../../include/Game/Entities/Monsters/Boar.h"
#include <random>
#include <chrono>

/**
 * @brief Constructs a Boar object with specified position, dimensions, and state.
 *
 * Initializes the Boar's animation, health, and scale.
 *
 * @param posX The x-coordinate of the Boar's position.
 * @param posY The y-coordinate of the Boar's position.
 * @param dimX The width of the Boar.
 * @param dimY The height of the Boar.
 * @param state The initial state of the Boar.
 */
Boar::Boar(const float posX, const float posY, const float dimX, const float dimY, const MonsterState state)
: Monster(posX, posY, dimX, dimY, state) {
    // Scale the boar
    Scale();
    // Load the boar animation
    boarAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(BOAR_RUNNING_TEXTURE_WHITE), BOAR_RUNNING_FRAMES, 0.1f, true);
    this->hp_ = BOAR_MAX_HEALTH;
}

#pragma region render methods

/**
 * @brief Draws the Boar to the screen.
 *
 * Uses the Boar's animation and position to render its current state.
 */
void Boar::Draw() {
    // Get the playerTexture sheet and currentRect from the Animation object
    Texture2D boarTexture = boarAnimation_->GetTexture();
    Rectangle currentRect = boarAnimation_->GetCurrentRect();
    boarAnimation_->FlipX(!movingRight_); // flip x axis based on the INVERSE of this flag, because boars face the opposite way in the sprite sheet
    // Draw the boar utilizing the currently loaded boarTexture, and rect position
    DrawTexturePro(boarTexture, currentRect, GetRect(), Vector2{0, 0}, 0, color_);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

/**
 * @brief Updates the Boar's behavior and animation.
 *
 * Handles animation, updates from the base Monster class, and determines if the Boar should "oink."
 */
void Boar::Update() {
    AnimateBoar();
    Monster::Update();
    timeSinceLastOink_ += GetFrameTime();
    MaybeOink();
}

/**
 * @brief Handles the Boar being hit.
 *
 * Reduces the Boar's health and notifies observers. If the health drops to zero, triggers the death animation.
 *
 * @param damage The amount of damage dealt to the Boar.
 */
void Boar::HitMonster(int damage) {
    // Run the base class code that's reusable
    Monster::HitMonster(damage);
    // Boar has died
    if (GetHealth() <= 0) {
        BeginDeathAnimation(); // play the death animation, then set shouldRemove_ to true after it fully plays
        Notify(this, EVENT_BOAR_DIED);
    }
    else {
        Notify(this, EVENT_BOAR_HIT); // Notify the boar has been hit, but didn't die
    }
}

/**
 * @brief Initiates the Boar's death animation.
 */
void Boar::BeginDeathAnimation() {
    if (state_ != DYING) {
        state_ = DYING;
        // load boar dying animation here
        boarAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(BOAR_DYING_TEXTURE_WHITE), BOAR_DYING_FRAMES, 0.10f, false);
    }
}

/**
 * @brief Animates the Boar.
 *
 * Updates the Boar's animation and checks if the death animation has completed.
 */
void Boar::AnimateBoar() {
    boarAnimation_->Animate();
    if (state_ == DYING && boarAnimation_->IsDone()) {
        Died();
    }
}

/**
 * @brief Determines if the Boar should "oink."
 *
 * The Boar randomly "oinks" within a range of 1 to 30 seconds. Notifies observers when it does.
 */
void Boar::MaybeOink() {
    if (timeSinceLastOink_ >= nextOinkTime_) { // Check if the time for the next oink has passed
        Notify(this, EVENT_BOAR_OINKED);
        timeSinceLastOink_ = 0.0f; // Reset the timer
        // Set the nextOinkTime randomly after an oink
            // using the C++11 random library
        // Create a random engine (seeded with the current time in ms)
        std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
        // Create a uniform distribution between 1 and 30
        std::uniform_real_distribution<float> distribution(1.0, 30.0);
        // Get the next oink time
        nextOinkTime_ = distribution(generator); // Set the time for the next oink to a random value between 1 and 30 seconds
    }
}

#pragma endregion

