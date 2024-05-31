//
// Created by ben on 5/29/24.
//

#include "../../../include/Entities/Objects/Tile.h"

Tile::Tile(float x, float y) : GameObject(TILE), texture_(TextureManager::GetInstance()->GetTexture(TILE_TEXTURE))
                               { // Ensure to instantiate the GameObject!
    dimensions_ = Vector2{128, 128};
    position_ = Vector2{x, y};
}

void Tile::SetTexture(GameTexture texture) {
    texture_ = texture;
}

void Tile::Draw() {
    DrawTexturePro(texture_.texture, texture_.rect, GetRect(), Vector2{0, 0}, 0, WHITE);     // Draw the texture
}

void Tile::Update() {

}

Tile::~Tile() = default;
