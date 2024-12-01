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
    // Use Raylib's LoadTexture, kinda confusing, but I don't have a better name for loading textures myself
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
    constexpr float treeWidth = 100;
    constexpr float treeHeight = 370;
    // Background
    const Texture2D backgroundTexture = ::LoadTexture(BACKGROUND_TEXTURE_PATH);
    TextureManager::LoadTexture(backgroundTexture, BACKGROUND_TEXTURE,
                                Rectangle{0, 0, static_cast<float>(backgroundTexture.width), static_cast<float>(backgroundTexture.height)});
    // Trees
    const Texture2D greenTreeTexture = ::LoadTexture(GREEN_TREE_TEXTURE_PATH);
    TextureManager::LoadTexture(greenTreeTexture, GREEN_TREE_TEXTURE,
                                Rectangle{0, 0, treeWidth, treeHeight});
    // Health Globe sprite sheet
    const Texture2D healthGlobeTexture = ::LoadTexture(HEALTH_GLOBE_TEXTURE_PATH);

    // Define the red square's portion of the sprite sheet
    constexpr float redSquareX = 95.0f;  // Fourth column
    constexpr float redSquareY = 255.0f;   // Second row
    constexpr float redSquareWidth = 25.0f;
    constexpr float redSquareHeight = 25.0f;

    // Add the red square texture using its rectangle
    TextureManager::LoadTexture(healthGlobeTexture, HEALTH_GLOBE_TEXTURE,
                                Rectangle{redSquareX, redSquareY, redSquareWidth, redSquareHeight});
}

// Load my monster textures
void TextureManager::LoadMonsterTextures() {
    // Boars
    TextureManager::LoadAnimatedTexture(BOAR_TEXTURE_RUNNING_PATH_WHITE, 0, BOAR_RUNNING_FRAMES, BOAR_RUNNING_TEXTURE_WHITE);
    TextureManager::LoadAnimatedTexture(BOAR_TEXTURE_DYING_PATH_WHITE, 0, BOAR_DYING_FRAMES, BOAR_DYING_TEXTURE_WHITE);
    TextureManager::LoadAnimatedTexture(BEE_TEXTURE_FLYING_PATH, 0, BEE_FLYING_FRAMES, BEE_FLYING_TEXTURE);
    TextureManager::LoadAnimatedTexture(SNAIL_TEXTURE_PATH, 0, SNAIL_FRAMES, SNAIL_TEXTURE);
}

GameTexture TextureManager::GetTexture(const TextureName textureName) {
    if (const auto it = Textures.find(textureName); it != Textures.end()) {
        return it->second;
    }
    // If texture not found
    TraceLog(LOG_ERROR, "Failed to load texture %s", TextureNameToString(textureName).c_str());
    throw std::invalid_argument("Texture not found.");
}

// My internal LoadTexture method that assigns a texture, name, and rect to the texture
void TextureManager::LoadTexture(const Texture2D &texture, const TextureName textureName, const Rectangle rect) {
    GameTexture gameTexture = {texture, rect};
    Emplace(textureName, gameTexture);
}

// Loads a texture with the frames taken into account
void TextureManager::LoadAnimatedTexture(const char * filePath, const int offset, const int frames, const TextureName textureName) {
    // Use raylibs LoadTexture
    const Texture2D texture = ::LoadTexture(filePath);
    const GameTexture gameTexture = {texture, Rectangle{0,
                                                 static_cast<float>(offset),
                                                 static_cast<float>(texture.width)/static_cast<float>(frames),
                                                 static_cast<float>(texture.height)}};
    Emplace(textureName, gameTexture);
}

// Emplace a texture into the TextureManager map
void TextureManager::Emplace(TextureName textureName, GameTexture gameTexture) {
    // emplace ensures the texture is not loaded twice
    Textures.emplace(std::pair<TextureName, GameTexture>(textureName, gameTexture));
}

// Destructor
TextureManager::~TextureManager() {
    for (const auto& gameTexture : Textures) {
        UnloadTexture(gameTexture.second.texture);
    }
}

std::string TextureManager::TextureNameToString(const TextureName name) {
    switch (name) {
        ENUM_TO_STRING_CASE(PLAYER_IDLE_TEXTURE)
        ENUM_TO_STRING_CASE(PLAYER_RUNNING_TEXTURE)
        ENUM_TO_STRING_CASE(PLAYER_JUMPING_TEXTURE)
        ENUM_TO_STRING_CASE(PLAYER_ATTACKING_TEXTURE)
        ENUM_TO_STRING_CASE(BOAR_RUNNING_TEXTURE_WHITE)
        ENUM_TO_STRING_CASE(BOAR_DYING_TEXTURE_WHITE)
        ENUM_TO_STRING_CASE(BEE_FLYING_TEXTURE)
        ENUM_TO_STRING_CASE(SNAIL_TEXTURE)
        ENUM_TO_STRING_CASE(BACKGROUND_TEXTURE)
        ENUM_TO_STRING_CASE(GREEN_TREE_TEXTURE)
        ENUM_TO_STRING_CASE(TILE_GRASS_TEXTURE)
        ENUM_TO_STRING_CASE(TILE_DIRT_TEXTURE)
        default: return "UNKNOWN_TEXTURE";
    }

}

