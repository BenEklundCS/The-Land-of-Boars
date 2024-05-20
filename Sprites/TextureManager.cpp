//
// Created by ben on 5/18/24.
//

#include "TextureManager.h"

std::map<std::string, GameTexture> TextureManager::Textures; // Define Textures

TextureManager::TextureManager() = default;

void TextureManager::LoadTextures() {
    Texture2D playerTexture = LoadTexture(PLAYER_TEXTURE_IDLE_PATH);
    GameTexture player = {playerTexture, Rectangle{0, -16, (float)playerTexture.width/4, (float)playerTexture.height}};
    Textures.insert(std::pair<std::string, GameTexture>("playerTexture", player));

    Texture2D backgroundTexture = LoadTexture(BACKGROUND_TEXTURE_PATH);
    GameTexture background = {backgroundTexture, Rectangle{0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height}};
    Textures.insert(std::pair<std::string, GameTexture>("backgroundTexture", background));
}

GameTexture TextureManager::GetTexture(const std::string& texture) {
    return Textures.at(texture);
}
