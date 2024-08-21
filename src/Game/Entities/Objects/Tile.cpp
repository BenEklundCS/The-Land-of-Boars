//
// Created by ben on 5/29/24.
//

#include "../../../../include/Game/Entities/Objects/Tile.h"

Tile::Tile(float x, float y, TextureName tileTexture) : GameObject(TILE), texture_(TextureManager::GetInstance()->GetTexture(tileTexture))
                               { // Ensure to instantiate the GameObject!
    dimensions_ = Vector2{TILE_LENGTH, TILE_LENGTH};
    position_ = Vector2{x, y};
}

void Tile::Draw() {
    DrawTexturePro(texture_.texture, texture_.rect, GetRect(), Vector2{0, 0}, 0, WHITE);     // Draw the texture
}

void Tile::Update() {

}

[[maybe_unused]] void Tile::SetTexture(GameTexture texture) {
    texture_ = texture;
}
