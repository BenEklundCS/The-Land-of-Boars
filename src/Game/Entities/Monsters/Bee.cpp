//
// Created by ben on 10/8/24.
//

#include "../../../../include/Game/Entities/Monsters/Bee.h"
#include "../../../../include/Game/Management/GameStateManager.h"


// Bee constructor
Bee::Bee(const float posX, const float posY, const float dimX, const float dimY, const MonsterState state)
: Monster(posX, posY, dimX, dimY, state) {
    // Scale the bee
    Scale();
    // Load the bee animation
    beeAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(BEE_FLYING_TEXTURE), BEE_FLYING_FRAMES, 0.1f, true);
    this->hp_ = BEE_MAX_HEALTH;
}

// Draw the bee
void Bee::Draw() {
    // Get the playerTexture sheet and currentRect from the Animation object
    const Texture2D beeTexture = beeAnimation_->GetTexture();
    const Rectangle currentRect = beeAnimation_->GetCurrentRect();
    beeAnimation_->FlipX(!movingRight_);
    // Draw the boar utilizing the currently loaded boarTexture, and rect position
    DrawTexturePro(beeTexture, currentRect, GetRect(), Vector2{0, 0}, 0, color_);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

// Update the bee
void Bee::Update() {
    AnimateBee();
    Monster::Update();
}

// Logic to call when the bee dies
void Bee::Died() {

}

bool Bee::InAttackRange() {
    // Get players from the GameStateManager
    /*
    auto players = GameStateManager::GetInstance()->GetPlayers();
    // Get relevant object positions
    std::vector<Vector2> playerPositions;
    playerPositions.reserve(players.size());
    for (const auto player : players) {
        playerPositions.push_back(player->GetPosition());
    }
    Vector2 beePosition = position_;
    // Use the distance formula to get the Bees distance to each player, and keep track of the closest player
    float closest = 500.0f; // arbitrary value larger than Bee max range.
    */
    return false; // dummy return for now
}

// Animate the bee
void Bee::AnimateBee() const {
    beeAnimation_->Animate();
}

// Override of hit monster
void Bee::HitMonster(const int damage) {
    Monster::HitMonster(damage);
}