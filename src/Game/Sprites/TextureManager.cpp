//
// Created by ben on 5/18/24.
//

#include "../../../include/Game/Sprites/TextureManager.h"
#include "stdexcept"

std::unique_ptr<TextureManager> TextureManager::instance = nullptr;

TextureManager::TextureManager() = default;

// Get the TextureManager object
TextureManager* TextureManager::GetInstance() {
    if (instance == nullptr) {
        instance = std::make_unique<TextureManager>();
        instance->LoadTextures();
    }
    return instance.get();
}

// Load all textures!
void TextureManager::LoadTextures() {
    // Load the textures
    LoadPlayerTextures();
    LoadTileTextures();
    LoadOtherTextures();
    LoadMonsterTextures();
}

// Load player textures
void TextureManager::LoadPlayerTextures() {
    // Player
    TextureManager::LoadAnimatedTexture(PLAYER_TEXTURE_IDLE_PATH, PLAYER_IDLESHEET_OFFSET, PLAYER_IDLE_FRAMES, PLAYER_IDLE_TEXTURE);
    TextureManager::LoadAnimatedTexture(PLAYER_TEXTURE_RUNNING_PATH, PLAYER_RUNSHEET_OFFSET, PLAYER_RUNNING_FRAMES, PLAYER_RUNNING_TEXTURE);
    TextureManager::LoadAnimatedTexture(PLAYER_TEXTURE_JUMPING_PATH, 0, PLAYER_JUMPING_FRAMES, PLAYER_JUMPING_TEXTURE);
    TextureManager::LoadAnimatedTexture(PLAYER_TEXTURE_ATTACKING_PATH, -16, PLAYER_ATTACKING_FRAMES, PLAYER_ATTACKING_TEXTURE);
}

// Load game tile textures
void TextureManager::LoadTileTextures() {
    // Use raylibs LoadTexture, kinda confusing, but I don't have a better name for loading textures myself
    Texture2D texture = ::LoadTexture(TILE_TEXTURE_PATH);
    float tileWidth = 64;
    float tileHeight = 64;
    TextureManager::LoadTexture(texture, TILE_GRASS_TEXTURE,
                                Rectangle{TILE_OFFSET, TILE_OFFSET, tileWidth, tileHeight});
    TextureManager::LoadTexture(texture, TILE_DIRT_TEXTURE,
                                Rectangle{TILE_OFFSET, TILE_OFFSET + TILE_LENGTH, tileWidth, tileHeight});
}

// Load all other textures
void TextureManager::LoadOtherTextures() {
    // Background
    // Use raylibs LoadTexture
    Texture2D backgroundTexture = ::LoadTexture(BACKGROUND_TEXTURE_PATH);
    TextureManager::LoadTexture(backgroundTexture, BACKGROUND_TEXTURE,
                                Rectangle{0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height});
}

// Load my monster textures
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
        throw std::invalid_argument("Texture not found.");
    }
}

// My internal LoadTexture method that assigns a texture, name, and rect to the texture
void TextureManager::LoadTexture(Texture2D texture, const std::string& textureName, Rectangle rect) {
    GameTexture gameTexture = {texture, rect};
    Emplace(textureName, gameTexture);
}

// Loads a texture with the frames taken into account
void TextureManager::LoadAnimatedTexture(const char * filePath, int offset, int frames, const std::string& textureName) {
    // Use raylibs LoadTexture
    Texture2D texture = ::LoadTexture(filePath);
    GameTexture gameTexture = {texture, Rectangle{0,
                                                 (float)offset,
                                                 (float)texture.width/(float)frames,
                                                 (float)texture.height}};
    Emplace(textureName, gameTexture);
}

// Emplace a texture into the TextureManager map
void TextureManager::Emplace(const std::string &textureName, GameTexture gameTexture) {
    // emplace ensures the texture is not loaded twice
    Textures.emplace(std::pair<std::string, GameTexture>(textureName, gameTexture));
}

// Destructor
TextureManager::~TextureManager() {
    for (const auto& gameTexture : Textures) {
        UnloadTexture(gameTexture.second.texture);
    }
}

