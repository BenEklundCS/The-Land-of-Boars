//
// Created by ben on 5/18/24.
//

#include "../../../include/Game/Sprites/TextureManager.h"
#include "stdexcept"

// Initialize the static instance for the TextureManager singleton
std::unique_ptr<TextureManager> TextureManager::instance = nullptr;

/**
 * @brief Default constructor for the TextureManager.
 */
TextureManager::TextureManager() = default;

/**
 * @brief Retrieve the singleton instance of TextureManager.
 *
 * This ensures only one instance of TextureManager exists during runtime.
 * If the instance does not already exist, it will be created, and textures
 * will be loaded automatically.
 *
 * @return TextureManager* Pointer to the singleton instance.
 */
TextureManager* TextureManager::GetInstance() {
    if (instance == nullptr) {
        instance = std::make_unique<TextureManager>();
        instance->LoadTextures();
    }
    return instance.get();
}

/**
 * @brief Load all necessary textures for the game.
 */
void TextureManager::LoadTextures() {
    // Load the textures
    LoadPlayerTextures();
    LoadTileTextures();
    LoadOtherTextures();
    LoadMonsterTextures();
}

/**
 * @brief Load textures specific to the player.
 */
void TextureManager::LoadPlayerTextures() {
    // Player
    TextureManager::LoadAnimatedTexture(PLAYER_TEXTURE_IDLE_PATH, PLAYER_IDLESHEET_OFFSET, PLAYER_IDLE_FRAMES, PLAYER_IDLE_TEXTURE);
    TextureManager::LoadAnimatedTexture(PLAYER_TEXTURE_RUNNING_PATH, PLAYER_RUNSHEET_OFFSET, PLAYER_RUNNING_FRAMES, PLAYER_RUNNING_TEXTURE);
    TextureManager::LoadAnimatedTexture(PLAYER_TEXTURE_JUMPING_PATH, 0, PLAYER_JUMPING_FRAMES, PLAYER_JUMPING_TEXTURE);
    TextureManager::LoadAnimatedTexture(PLAYER_TEXTURE_ATTACKING_PATH, -16, PLAYER_ATTACKING_FRAMES, PLAYER_ATTACKING_TEXTURE);
}

/**
 * @brief Load textures for the game's tiles.
 */
void TextureManager::LoadTileTextures() {
    // Use Raylib's LoadTexture, kinda confusing, but I don't have a better name for loading textures myself
    Texture2D texture = ::LoadTexture(TILE_TEXTURE_PATH);
    constexpr float tileWidth = 64;
    constexpr float tileHeight = 64;
    TextureManager::LoadTexture(texture, TILE_GRASS_TEXTURE,
                                Rectangle{TILE_OFFSET, TILE_OFFSET, tileWidth, tileHeight});
    TextureManager::LoadTexture(texture, TILE_DIRT_TEXTURE,
                                Rectangle{TILE_OFFSET, TILE_OFFSET + TILE_LENGTH, tileWidth, tileHeight});
}

/**
 * @brief Load other miscellaneous textures like trees and backgrounds.
 */
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
    const Texture2D healthGlobeTexture = ::LoadTexture(HUD_BASE_TEXTURE_PATH);

    // Define the red square's portion of the sprite sheet
    constexpr float redSquareX = 95.0f;  // Fourth column
    constexpr float redSquareY = 255.0f;   // Second row
    constexpr float redSquareWidth = 25.0f;
    constexpr float redSquareHeight = 25.0f;

    // Add the red square texture using its rectangle
    TextureManager::LoadTexture(healthGlobeTexture, HEALTH_GLOBE_TEXTURE,
                                Rectangle{redSquareX, redSquareY, redSquareWidth, redSquareHeight});

    const Texture2D coinTexture = ::LoadTexture(HUD_BASE_TEXTURE_PATH);

    // Define the coin's portion of the sprite sheet
    constexpr float coinX = 20.0f;
    constexpr float coinY = 212.0f;
    constexpr float coinWidth = 10.0f;
    constexpr float coinHeight = 10.0f;

    // Add the coin texture using its rectangle
    TextureManager::LoadTexture(coinTexture, COIN_TEXTURE,
                                Rectangle{coinX, coinY, coinWidth, coinHeight});

    // Load button texture (blue)
    constexpr float bbuttonX = 243.0f;
    constexpr float bbuttonY = 59.0f;
    constexpr float bbuttonWidth = 60.0f;
    constexpr float bbuttonHeight = 26.0f;

    TextureManager::LoadTexture(coinTexture, BLUE_BUTTON_TEXTURE,
                                Rectangle{bbuttonX, bbuttonY, bbuttonWidth, bbuttonHeight});
}

/**
 * @brief Load textures for monsters such as boars, bees, and snails.
 */
void TextureManager::LoadMonsterTextures() {
    // Boars
    TextureManager::LoadAnimatedTexture(BOAR_TEXTURE_RUNNING_PATH_WHITE, 0, BOAR_RUNNING_FRAMES, BOAR_RUNNING_TEXTURE_WHITE);
    TextureManager::LoadAnimatedTexture(BOAR_TEXTURE_DYING_PATH_WHITE, 0, BOAR_DYING_FRAMES, BOAR_DYING_TEXTURE_WHITE);
    TextureManager::LoadAnimatedTexture(BEE_TEXTURE_FLYING_PATH, 0, BEE_FLYING_FRAMES, BEE_FLYING_TEXTURE);
    TextureManager::LoadAnimatedTexture(BEE_DYING_TEXTURE_PATH, 0, BEE_DYING_FRAMES, BEE_DYING_TEXTURE);
    TextureManager::LoadAnimatedTexture(SNAIL_TEXTURE_PATH, 0, SNAIL_FRAMES, SNAIL_TEXTURE);
    TextureManager::LoadAnimatedTexture(SNAIL_DYING_TEXTURE_PATH, 0, SNAIL_DYING_FRAMES, SNAIL_DYING_TEXTURE);
}

/**
 * @brief Retrieves a GameTexture by its name.
 *
 * @param textureName The identifier for the texture.
 * @return GameTexture The texture and its associated rectangle.
 * @throws std::invalid_argument If the texture is not found.
 */
GameTexture TextureManager::GetTexture(const TextureName textureName) {
    if (const auto it = Textures.find(textureName); it != Textures.end()) {
        return it->second;
    }
    // If texture not found
    TraceLog(LOG_ERROR, "Failed to load texture %s", TextureNameToString(textureName).c_str());
    throw std::invalid_argument("Texture not found.");
}

/**
 * @brief Load a static texture and map it to a TextureName.
 *
 * @param texture The loaded texture object.
 * @param textureName The identifier for the texture.
 * @param rect The rectangle defining the texture's bounds.
 */
void TextureManager::LoadTexture(const Texture2D &texture, const TextureName textureName, const Rectangle rect) {
    const GameTexture gameTexture = {texture, rect};
    Emplace(textureName, gameTexture);
}

/**
 * @brief Load an animated texture with frame information.
 *
 * @param filePath The file path to the texture.
 * @param offset The vertical offset for the texture.
 * @param frames The number of animation frames.
 * @param textureName The identifier for the texture.
 */
void TextureManager::LoadAnimatedTexture(const char * filePath, const int offset, const int frames, const TextureName textureName) {
    // Use raylibs LoadTexture
    const Texture2D texture = ::LoadTexture(filePath);
    const GameTexture gameTexture = {texture, Rectangle{0,
                                                 static_cast<float>(offset),
                                                 static_cast<float>(texture.width)/static_cast<float>(frames),
                                                 static_cast<float>(texture.height)}};
    Emplace(textureName, gameTexture);
}

/**
 * @brief Add a texture to the internal map.
 *
 * @param textureName The identifier for the texture.
 * @param gameTexture The GameTexture object containing the texture and rectangle.
 */
void TextureManager::Emplace(TextureName textureName, GameTexture gameTexture) {
    // emplace ensures the texture is not loaded twice
    Textures.emplace(std::pair<TextureName, GameTexture>(textureName, gameTexture));
}


/**
 * @brief Destructor for the TextureManager.
 *
 * Ensures all loaded textures are properly unloaded to free resources.
 */
TextureManager::~TextureManager() {
    for (const auto&[fst, snd] : Textures) {
        UnloadTexture(snd.texture);
    }
}

/**
 * @brief Convert a TextureName to its string representation.
 *
 * @param name The texture name.
 * @return std::string The string representation.
 */
std::string TextureManager::TextureNameToString(const TextureName name) {
    switch (name) {
        ENUM_TO_STRING_CASE(PLAYER_IDLE_TEXTURE)
        ENUM_TO_STRING_CASE(PLAYER_RUNNING_TEXTURE)
        ENUM_TO_STRING_CASE(PLAYER_JUMPING_TEXTURE)
        ENUM_TO_STRING_CASE(PLAYER_ATTACKING_TEXTURE)
        ENUM_TO_STRING_CASE(BOAR_RUNNING_TEXTURE_WHITE)
        ENUM_TO_STRING_CASE(BOAR_DYING_TEXTURE_WHITE)
        ENUM_TO_STRING_CASE(BEE_FLYING_TEXTURE)
        ENUM_TO_STRING_CASE(BEE_DYING_TEXTURE)
        ENUM_TO_STRING_CASE(SNAIL_TEXTURE)
        ENUM_TO_STRING_CASE(SNAIL_DYING_TEXTURE)
        ENUM_TO_STRING_CASE(BACKGROUND_TEXTURE)
        ENUM_TO_STRING_CASE(GREEN_TREE_TEXTURE)
        ENUM_TO_STRING_CASE(TILE_GRASS_TEXTURE)
        ENUM_TO_STRING_CASE(TILE_DIRT_TEXTURE)
        ENUM_TO_STRING_CASE(BLUE_BUTTON_TEXTURE)
        ENUM_TO_STRING_CASE(HEALTH_GLOBE_TEXTURE)
        default: return "UNKNOWN_TEXTURE";
    }

}

