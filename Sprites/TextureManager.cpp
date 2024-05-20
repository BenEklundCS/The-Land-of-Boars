//
// Created by ben on 5/18/24.
//

#include "TextureManager.h"

std::map<std::string, GameTexture> TextureManager::Textures; // Define Textures

TextureManager::TextureManager() = default;

void TextureManager::LoadTextures() {
    Texture2D playerIdleTexture = LoadTexture(PLAYER_TEXTURE_IDLE_PATH);
    GameTexture playerIdle = {playerIdleTexture, Rectangle{0, -16, (float)playerIdleTexture.width/4, (float)playerIdleTexture.height}};
    Textures.insert(std::pair<std::string, GameTexture>(PLAYER_IDLE_TEXTURE, playerIdle));

    Texture2D playerRunningTexture = LoadTexture(PLAYER_TEXTURE_RUNNING_PATH);
    GameTexture playerRunning = {playerRunningTexture, Rectangle{0, -12, (float)playerRunningTexture.width/8, (float)playerRunningTexture.height}};
    Textures.insert(std::pair<std::string, GameTexture>(PLAYER_RUNNING_TEXTURE, playerRunning));

    Texture2D backgroundTexture = LoadTexture(BACKGROUND_TEXTURE_PATH);
    GameTexture background = {backgroundTexture, Rectangle{0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height}};
    Textures.insert(std::pair<std::string, GameTexture>(BACKGROUND_TEXTURE, background));
}

GameTexture TextureManager::GetTexture(const std::string& texture) {
    return Textures.at(texture);
}
