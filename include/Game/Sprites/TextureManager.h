//
// Created by ben on 5/18/24.
//

/*
 * The following is essentially a hardcoded texture loader with hardcoded paths to my development directory
 *
 */

#ifndef PLATFORMER_TEXTUREMANAGER_H
#define PLATFORMER_TEXTUREMANAGER_H

#include <memory>
#include <map>
#include <string>
#include "raylib.h"

#pragma region path_definitions

// Player paths
#define PLAYER_TEXTURE_IDLE_PATH "../Assets/Sprites/Character/Idle/Idle-Sheet.png"
#define PLAYER_TEXTURE_RUNNING_PATH "../Assets/Sprites/Character/Run/Run-Sheet.png"
#define PLAYER_TEXTURE_JUMPING_PATH "../Assets/Sprites/Character/Jumlp-All/Jump-All-Sheet.png"
#define PLAYER_TEXTURE_ATTACKING_PATH "../Assets/Sprites/Character/Attack-01/Attack-01-Sheet.png"

// Background path
#define BACKGROUND_TEXTURE_PATH "../Assets/Sprites/Background/Background.png"

#define TILE_TEXTURE_PATH "../Assets/Sprites/Assets/Tiles.png" // Texture path

#define GREEN_TREE_TEXTURE_PATH "../Assets/Sprites/Trees/Green-Tree.png"

#define BOAR_TEXTURE_RUNNING_PATH_WHITE "../Assets/Sprites/Mob/Boar/Run/Run-Sheet-White.png"
#define BOAR_TEXTURE_DYING_PATH_WHITE "../Assets/Sprites/Mob/Boar/Hit-Vanish/Hit-Sheet-White.png"

#define BEE_TEXTURE_FLYING_PATH "../Assets/Sprites/Mob/Small Bee/Fly/Fly-Sheet.png"
#define BEE_DYING_TEXTURE_PATH "../Assets/Sprites/Mob/Small Bee/Hit/Hit-Sheet.png"

#define SNAIL_TEXTURE_PATH "../Assets/Sprites/Mob/Snail/walk-Sheet.png"
#define SNAIL_DYING_TEXTURE_PATH "../Assets/Sprites/Mob/Snail/Dead-Sheet.png"

// All HUD icons
#define HUD_BASE_TEXTURE_PATH "../Assets/Sprites/HUD/Base.png"

#pragma endregion

#pragma constants

// Player frame counts
#define PLAYER_IDLE_FRAMES 4
#define PLAYER_RUNNING_FRAMES 8
#define PLAYER_JUMPING_FRAMES 15
#define PLAYER_ATTACKING_FRAMES 8

// Player Spritesheet offsets
#define PLAYER_IDLESHEET_OFFSET (-16)
#define PLAYER_RUNSHEET_OFFSET (-12)

// Boars
#define BOAR_RUNNING_FRAMES 6
#define BOAR_DYING_FRAMES 4

// Bees
#define BEE_FLYING_FRAMES 4
#define BEE_DYING_FRAMES 4

// Snails
#define SNAIL_FRAMES 8
#define SNAIL_DYING_FRAMES 8


// Tiles
#define TILE_LENGTH 80 // size of a tile
#define TILE_OFFSET 10 // starting offset to get tile from spritesheet

// Trees
#define TREE_WIDTH 400
#define TREE_HEIGHT 1000

#pragma endregion

#pragma region texturename

// Macro to automate the string conversion
#define ENUM_TO_STRING_CASE(name) case name: return #name;

enum TextureName {
    // Player
    PLAYER_IDLE_TEXTURE,
    PLAYER_RUNNING_TEXTURE,
    PLAYER_JUMPING_TEXTURE,
    PLAYER_ATTACKING_TEXTURE,
    // Monsters
    // Boars
    BOAR_RUNNING_TEXTURE_WHITE,
    BOAR_DYING_TEXTURE_WHITE,
    // Bees
    BEE_FLYING_TEXTURE,
    BEE_DYING_TEXTURE,
    // Snails
    SNAIL_TEXTURE,
    SNAIL_DYING_TEXTURE,
    // Background
    BACKGROUND_TEXTURE,
    // Trees
    GREEN_TREE_TEXTURE,
    // Tiles
    TILE_GRASS_TEXTURE,
    TILE_DIRT_TEXTURE,
    // UI
    HEALTH_GLOBE_TEXTURE,
    // Collectables
    COIN_TEXTURE
};

#pragma endregion

/**
 * @struct GameTexture
 * Struct representing a texture and its associated rectangle.
 *
 * This struct encapsulates a `Texture2D` object and a `Rectangle` defining the portion of the texture to use.
 */
struct GameTexture {
    Texture2D texture; ///< The loaded texture.
    Rectangle rect;    ///< The rectangle defining the texture's region.
};

/**
 * @class TextureManager
 * @brief Singleton class for managing game textures.
 *
 * The `TextureManager` handles the loading and retrieval of textures used in the game.
 * It ensures all textures are loaded once and provides an interface to access them.
 */
class TextureManager {
private:
    static std::unique_ptr<TextureManager> instance; ///< Singleton instance of the `TextureManager`.
    std::map<TextureName, GameTexture> Textures;     ///< Map of loaded textures.

    /**
     * @brief Loads an animated texture from a sprite sheet.
     * @param filePath Path to the sprite sheet.
     * @param offset Starting offset for the texture in the sprite sheet.
     * @param frames Number of animation frames in the sprite sheet.
     * @param textureName The `TextureName` key for the texture.
     */
    void LoadAnimatedTexture(const char * filePath, int offset, int frames, TextureName textureName);

    /**
     * @brief Loads a static texture and its rectangle.
     * @param texture The `Texture2D` object.
     * @param textureName The `TextureName` key for the texture.
     * @param rect The rectangle defining the texture's region.
     */
    void LoadTexture(const Texture2D &texture, TextureName textureName, Rectangle rect);

    /**
     * @brief Adds a texture to the internal map.
     * @param textureName The `TextureName` key for the texture.
     * @param gameTexture The `GameTexture` to store.
     */
    void Emplace(TextureName textureName, GameTexture gameTexture);

    /**
     * @brief Loads player-related textures.
     */
    void LoadPlayerTextures();

    /**
     * @brief Loads tile-related textures.
     */
    void LoadTileTextures();

    /**
     * @brief Loads monster-related textures.
     */
    void LoadMonsterTextures();

    /**
     * @brief Loads miscellaneous textures (e.g., background, HUD).
     */
    void LoadOtherTextures();

    /**
     * @brief Converts a `TextureName` to its string representation.
     * @param name The `TextureName` to convert.
     * @return A string representation of the texture name.
     */
    static std::string TextureNameToString(TextureName name);

public:
    /**
     * @brief Default constructor for the `TextureManager`.
     */
    TextureManager();

    /**
     * @brief Retrieves the singleton instance of the `TextureManager`.
     * @return Pointer to the `TextureManager` instance.
     */
    static TextureManager* GetInstance();

    /**
     * @brief Loads all textures into the manager.
     *
     * This method loads player, tile, monster, and other textures into memory.
     */
    void LoadTextures();

    /**
     * @brief Retrieves a texture by name.
     * @param textureName The name of the texture to retrieve.
     * @return The `GameTexture` associated with the given `TextureName`.
     * @throws std::invalid_argument if the texture name is not found.
     */
    GameTexture GetTexture(TextureName textureName);

    /**
     * @brief Destructor for the `TextureManager`.
     *
     * Unloads all textures managed by the class.
     */
    ~TextureManager();
};

#endif //PLATFORMER_TEXTUREMANAGER_H

