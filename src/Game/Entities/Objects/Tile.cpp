//
// Created by ben on 5/29/24.
//

#include "../../../../include/Game/Entities/Objects/Tile.h"

Tile::Tile(const float x, const float y, const TextureName tileTexture) : GameObject(TILE) {
    // Ensure to instantiate the GameObject!
    dimensions_ = Vector2{TILE_LENGTH, TILE_LENGTH};
    position_ = Vector2{x, y};
    // Scale the game object
    Scale();
    // Load the texture
    texture_ = TextureManager::GetInstance()->GetTexture(tileTexture);
}

void Tile::Draw() {
    DrawTexturePro(texture_.texture, texture_.rect, GetRect(), Vector2{0, 0}, 0, WHITE);     // Draw the texture
}

void Tile::Update() {

}

[[maybe_unused]] void Tile::SetTexture(const GameTexture &texture) {
    texture_ = texture;
}
