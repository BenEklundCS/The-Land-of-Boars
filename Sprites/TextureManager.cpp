//
// Created by ben on 5/18/24.
//

#include "TextureManager.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager() = default;

TextureManager *TextureManager::GetInstance() {
    if (instance == nullptr) {
        instance = new TextureManager();
        instance->LoadTextures();
    }
    return instance;
}

void TextureManager::LoadTextures() {
    // Player IDLE texture sheet
    Texture2D playerIdleTexture = LoadTexture(PLAYER_TEXTURE_IDLE_PATH);
    GameTexture playerIdle = {playerIdleTexture, Rectangle{0,
                                                           PLAYER_IDLESHEET_OFFSET,
                                                           (float)playerIdleTexture.width/PLAYER_IDLE_FRAMES,
                                                           (float)playerIdleTexture.height}};
    Textures.insert(std::pair<std::string, GameTexture>(PLAYER_IDLE_TEXTURE, playerIdle));

    // Player RUNNING texture sheet
    Texture2D playerRunningTexture = LoadTexture(PLAYER_TEXTURE_RUNNING_PATH);
    GameTexture playerRunning = {playerRunningTexture, Rectangle{0,
                                                                 PLAYER_RUNSHEET_OFFSET,
                                                                 (float)playerRunningTexture.width/PLAYER_RUNNING_FRAMES,
                                                                 (float)playerRunningTexture.height}};
    Textures.insert(std::pair<std::string, GameTexture>(PLAYER_RUNNING_TEXTURE, playerRunning));

    Texture2D playerJumpingTexture = LoadTexture(PLAYER_TEXTURE_JUMPING_PATH);
    GameTexture playerJumping = {playerJumpingTexture, Rectangle{0,
                                                                 0,
                                                                 (float)playerJumpingTexture.width/PLAYER_JUMPING_FRAMES,
                                                                 (float)playerJumpingTexture.height}};
    Textures.insert(std::pair<std::string, GameTexture>(PLAYER_JUMPING_TEXTURE, playerJumping));

    // Background Texture
    Texture2D backgroundTexture = LoadTexture(BACKGROUND_TEXTURE_PATH);
    GameTexture background = {backgroundTexture, Rectangle{0, 0,
                                                           (float)backgroundTexture.width,
                                                           (float)backgroundTexture.height}};
    Textures.insert(std::pair<std::string, GameTexture>(BACKGROUND_TEXTURE, background));
}

GameTexture TextureManager::GetTexture(const std::string& texture) {
    return Textures.at(texture);
}

TextureManager::~TextureManager() {
    for (const auto& gameTexture : Textures) {
        UnloadTexture(gameTexture.second.texture);
    }
}
