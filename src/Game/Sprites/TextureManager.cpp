//
// Created by ben on 5/18/24.
//



#include "../../../include/Game/Sprites/TextureManager.h"

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
    LoadPlayerTextures();
    LoadTileTextures();
    LoadOtherTextures();
    LoadMonsterTextures();
}

void TextureManager::LoadPlayerTextures() {
    // Player
    TextureManager::LoadAnimatedTexture(PLAYER_TEXTURE_IDLE_PATH, PLAYER_IDLESHEET_OFFSET, PLAYER_IDLE_FRAMES, PLAYER_IDLE_TEXTURE);
    TextureManager::LoadAnimatedTexture(PLAYER_TEXTURE_RUNNING_PATH, PLAYER_RUNSHEET_OFFSET, PLAYER_RUNNING_FRAMES, PLAYER_RUNNING_TEXTURE);
    TextureManager::LoadAnimatedTexture(PLAYER_TEXTURE_JUMPING_PATH, 0, PLAYER_JUMPING_FRAMES, PLAYER_JUMPING_TEXTURE);
}

void TextureManager::LoadTileTextures() {
    Texture2D grassTexture = ::LoadTexture(TILE_TEXTURE_PATH);
    TextureManager::LoadTexture(grassTexture, TILE_TEXTURE, Rectangle{0, 0, (float)grassTexture.width/5, (float)grassTexture.height/5});
}

void TextureManager::LoadOtherTextures() {
    // Background
    Texture2D backgroundTexture = ::LoadTexture(BACKGROUND_TEXTURE_PATH);
    TextureManager::LoadTexture(backgroundTexture, BACKGROUND_TEXTURE, Rectangle{0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height});
}

void TextureManager::LoadMonsterTextures() {
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

void TextureManager::LoadTexture(Texture2D texture, const std::string& textureName, Rectangle rect) {
    GameTexture gameTexture = {texture, rect};
    Emplace(textureName, gameTexture);
}

void TextureManager::LoadAnimatedTexture(const char * filePath, int offset, int frames, const std::string& textureName) {
    Texture2D texture = ::LoadTexture(filePath);
    GameTexture gameTexture = {texture, Rectangle{0,
                                                 (float)offset,
                                                 (float)texture.width/(float)frames,
                                                 (float)texture.height}};
    Emplace(textureName, gameTexture);
}

void TextureManager::Emplace(const std::string &textureName, GameTexture gameTexture) {
    Textures.emplace(std::pair<std::string, GameTexture>(textureName, gameTexture));
}

