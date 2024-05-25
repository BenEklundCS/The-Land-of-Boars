//
// Created by ben on 5/18/24.
//

#include "TextureManager.h"

std::unique_ptr<TextureManager> TextureManager::instance = nullptr;

TextureManager::TextureManager() = default;

TextureManager* TextureManager::GetInstance() {
    if (instance == nullptr) {
        instance = std::make_unique<TextureManager>();
        instance->LoadTextures();
    }
    return instance.get();
}

void TextureManager::LoadTextures() {
    // Player IDLE texture sheet
    Texture2D playerIdleTexture = LoadTexture(PLAYER_TEXTURE_IDLE_PATH);
    GameTexture playerIdle = {playerIdleTexture, Rectangle{0,
                                                           PLAYER_IDLESHEET_OFFSET,
                                                           (float)playerIdleTexture.width/PLAYER_IDLE_FRAMES,
                                                           (float)playerIdleTexture.height}};
    Textures.emplace(std::pair<std::string, GameTexture>(PLAYER_IDLE_TEXTURE, playerIdle));

    // Player RUNNING texture sheet
    Texture2D playerRunningTexture = LoadTexture(PLAYER_TEXTURE_RUNNING_PATH);
    GameTexture playerRunning = {playerRunningTexture, Rectangle{0,
                                                                 PLAYER_RUNSHEET_OFFSET,
                                                                 (float)playerRunningTexture.width/PLAYER_RUNNING_FRAMES,
                                                                 (float)playerRunningTexture.height}};
    Textures.emplace(std::pair<std::string, GameTexture>(PLAYER_RUNNING_TEXTURE, playerRunning));

    Texture2D playerJumpingTexture = LoadTexture(PLAYER_TEXTURE_JUMPING_PATH);
    GameTexture playerJumping = {playerJumpingTexture, Rectangle{0,
                                                                 0,
                                                                 (float)playerJumpingTexture.width/PLAYER_JUMPING_FRAMES,
                                                                 (float)playerJumpingTexture.height}};
    Textures.emplace(std::pair<std::string, GameTexture>(PLAYER_JUMPING_TEXTURE, playerJumping));

    // Background Texture
    Texture2D backgroundTexture = LoadTexture(BACKGROUND_TEXTURE_PATH);
    GameTexture background = {backgroundTexture, Rectangle{0, 0,
                                                           (float)backgroundTexture.width,
                                                           (float)backgroundTexture.height}};
    Textures.emplace(std::pair<std::string, GameTexture>(BACKGROUND_TEXTURE, background));

    // Boar texture
    Texture2D boarTexture = LoadTexture(BOAR_TEXTURE_RUNNING_PATH_WHITE);
    GameTexture boar = {boarTexture, Rectangle{0, 0,
                                               (float)boarTexture.width/BOAR_RUNNING_FRAMES,
                                               (float)boarTexture.height}};
    Textures.emplace(std::pair<std::string, GameTexture>(BOAR_RUNNING_TEXTURE_WHITE, boar));
}

GameTexture TextureManager::GetTexture(const std::string& texture) {
    if (Textures.find(texture) != Textures.end()) {
        return Textures.at(texture);
    }
    else {
        TraceLog(LOG_ERROR, "Failed to load texture %s", texture.c_str());
    }
}

TextureManager::~TextureManager() {
    for (const auto& gameTexture : Textures) {
        UnloadTexture(gameTexture.second.texture);
    }
}
