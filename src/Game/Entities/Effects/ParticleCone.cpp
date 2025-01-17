#include "../../../include/Game/Entities/Effects/ParticleCone.h"
#include "cmath"

/**
 * @brief Constructs a ParticleCone object, representing a particle effect emanating in a cone shape.
 *
 * @param position The starting position of the particle cone.
 * @param playerDimensions The dimensions of the player, used for positioning the cone relative to the player.
 * @param facingRight Whether the cone is facing right (true) or left (false).
 * @param particleCount The initial number of particles to spawn in the cone.
 */
ParticleCone::ParticleCone(const Vector2 position, const Vector2 playerDimensions, const bool facingRight, const float particleCount) {
    position_ = position;
    playerDimensions_ = playerDimensions;
    facingRight_ = facingRight;
    particleCount_ = particleCount;
}

/**
 * @brief Renders the particle cone on the screen.
 *
 * Particles are spawned in a randomized cone shape, with their positions determined by the cone's base angle, spread,
 * and randomized distance from the origin.
 */
void ParticleCone::Draw() {
    // Number of particles to draw
    const int particles = static_cast<int>(particleCount_);

    // Determine the direction based on whether the object is facing right or left
    const float baseAngle = facingRight_ ? 0.0f : PI;

    // Adjust the initial position based on the player's direction and dimensions
    auto [x, y] = position_;
    if (facingRight_) {
        x += playerDimensions_.x;  // Spawn at the front-right edge
    } else {
        x -= playerDimensions_.x;  // Spawn at the front-left edge
    }

    // Loop through each particle
    for (int i = 0; i < particles; i++) {
        // Randomize the spread within the cone
        const float spread = static_cast<float>(GetRandomValue(-15, 15)) * DEG2RAD;
        const float angle = baseAngle + spread;

        // Randomize the distance of the particle from the origin
        const auto distance = static_cast<float>(GetRandomValue(0, 300));  // Adjusted distance for particles

        // Calculate the particle's position
        const Vector2 particlePosition = {
                x + cosf(angle) * distance + 60,
                y + sinf(angle) * distance + 100
        };

        // Draw the particle as a small circle or a texture
        DrawCircleV(particlePosition, 2.5, WHITE);  // Adjust the size and color as needed
    }
}



void ParticleCone::Update() {
    // Decrease the particle count over time
    particleCount_ -= particleCount_/5; // Decrease particle count proportionally to the frame rate
    if (particleCount_ <= 5) {
        // Mark the effect for removal
        shouldRemove_ = true;
    }
}

bool ParticleCone::ShouldRemove() const {
    return shouldRemove_;
}