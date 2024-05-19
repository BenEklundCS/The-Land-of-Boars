//
// Created by ben on 5/18/24.
//

#include "TextureManager.h"

std::map<std::string, Texture2D> TextureManager::Textures; // Define Textures
std::map<std::string, Rectangle> TextureManager::Rects; // Define Textures

TextureManager::TextureManager() {

}

void TextureManager::LoadTextures() {
    Textures.insert(std::pair<std::string, Texture2D>("playerTexture", LoadTexture(PLAYER_TEXTURE_IDLE_PATH)));
    Rects.insert(std::pair<std::string, Rectangle>("playerRect", Rectangle{0, 0, 64, 64}));
    Textures.insert(std::pair<std::string, Texture2D>("backgroundTexture", LoadTexture(BACKGROUND_TEXTURE_PATH)));
    Rects.insert(std::pair<std::string, Rectangle>("backgroundRect", Rectangle{0, 0, 480, 270}));
}

Texture2D TextureManager::GetTexture(const std::string& texture) {
    return Textures.at(texture);
}

Rectangle TextureManager::GetRect(const std::string &rect) {
    return Rects.at(rect);
}
