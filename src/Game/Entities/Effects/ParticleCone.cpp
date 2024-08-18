#include "../../../include/Game/Entities/Effects/ParticleCone.h"
#include "cmath"

ParticleCone::ParticleCone(Vector2 position, Vector2 playerDimensions, bool movingRight, float particleCount) {
    position_ = position;
    playerDimensions_ = playerDimensions;
    facingRight_ = movingRight;
    particleCount_ = particleCount;
}

void ParticleCone::Draw() {
    // Number of particles to draw
    int particles = static_cast<int>(particleCount_);

    // Determine the direction based on whether the object is facing right or left
    float baseAngle = facingRight_ ? 0.0f : PI;

    // Adjust the initial position based on the player's direction and dimensions
    Vector2 initialPosition = position_;
    if (facingRight_) {
        initialPosition.x += playerDimensions_.x;  // Spawn at the front-right edge
    } else {
        initialPosition.x -= playerDimensions_.x;  // Spawn at the front-left edge
    }

    // Loop through each particle
    for (int i = 0; i < particles; i++) {
        // Randomize the spread within the cone
        float spread = GetRandomValue(-15, 15) * DEG2RAD;
        float angle = baseAngle + spread;

        // Randomize the distance of the particle from the origin
        float distance = GetRandomValue(0, 300);  // Adjusted distance for particles

        // Calculate the particle's position
        Vector2 particlePosition = {
                initialPosition.x + cosf(angle) * distance + 60,
                initialPosition.y + sinf(angle) * distance + 100
        };

        // Draw the particle as a small circle or a texture
        DrawCircleV(particlePosition, 2.5, WHITE);  // Adjust the size and color as needed
    }
}



void ParticleCone::Update() {
    // Decrease the particle count over time
    particleCount_ -= particleCount_/5; // Decrease particle count proportionally to the frame rate
    if (particleCount_ <= 0) {
        // Mark the effect for removal
        shouldRemove_ = true;
    }
}

bool ParticleCone::ShouldRemove() const {
    return shouldRemove_;
}