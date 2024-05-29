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
    // Load the textures
    // Player
    TextureManager::LoadAnimatedTexture(PLAYER_TEXTURE_IDLE_PATH, PLAYER_IDLESHEET_OFFSET, PLAYER_IDLE_FRAMES, PLAYER_IDLE_TEXTURE);
    TextureManager::LoadAnimatedTexture(PLAYER_TEXTURE_RUNNING_PATH, PLAYER_RUNSHEET_OFFSET, PLAYER_RUNNING_FRAMES, PLAYER_RUNNING_TEXTURE);
    TextureManager::LoadAnimatedTexture(PLAYER_TEXTURE_JUMPING_PATH, 0, PLAYER_JUMPING_FRAMES, PLAYER_JUMPING_TEXTURE);
    // Background
    TextureManager::LoadStaticTexture(BACKGROUND_TEXTURE_PATH, BACKGROUND_TEXTURE);
    // Boars
    TextureManager::LoadAnimatedTexture(BOAR_TEXTURE_RUNNING_PATH_WHITE, 0, BOAR_RUNNING_FRAMES, BOAR_RUNNING_TEXTURE_WHITE);

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

void TextureManager::LoadStaticTexture(const char *filePath, const std::string& textureName) {
    Texture2D texture = ::LoadTexture(filePath);
    GameTexture gameTexture = {texture, Rectangle{0,
                                                  0,
                                                  (float)texture.width,
                                                  (float)texture.height}};
    Emplace(textureName, gameTexture);
}

void TextureManager::LoadAnimatedTexture(const char * filePath, int offset, int frames, const std::string& textureName) {
    Texture2D texture = ::LoadTexture(filePath);
    GameTexture gameTexture = {texture, Rectangle{0,
                                                 (float)offset,
                                                 (float)texture.width/frames,
                                                 (float)texture.height}};
    Emplace(textureName, gameTexture);
}

void TextureManager::Emplace(const std::string &textureName, GameTexture gameTexture) {
    Textures.emplace(std::pair<std::string, GameTexture>(textureName, gameTexture));
}

