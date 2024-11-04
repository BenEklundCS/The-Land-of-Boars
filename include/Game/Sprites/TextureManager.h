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

#define SNAIL_TEXTURE_PATH "../Assets/Sprites/Mob/Snail/walk-Sheet.png"

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

// Snails
#define SNAIL_FRAMES 8

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
    // Snails
    SNAIL_TEXTURE,
    // Background
    BACKGROUND_TEXTURE,
    // Trees
    GREEN_TREE_TEXTURE,
    // Tiles
    TILE_GRASS_TEXTURE,
    TILE_DIRT_TEXTURE

};

#pragma endregion

struct GameTexture {
    Texture2D texture;
    Rectangle rect;
};

// Texture Manager loads all textures as a Singleton, and has a GetTexture method to retrieve loaded texture objects
class TextureManager {
private:
    static std::unique_ptr<TextureManager> instance; // Instance of texture manager
    std::map<TextureName, GameTexture> Textures; // Map of textures
    void LoadAnimatedTexture(const char * filePath, int offset, int frames, TextureName textureName);
    void LoadTexture(const Texture2D &texture, TextureName textureName, Rectangle rect); // Load a texture
    void Emplace(TextureName textureName, GameTexture gameTexture); // Emplace a texture into the texture map
    void LoadPlayerTextures(); // Load player textures
    void LoadTileTextures(); // Load tile textures
    void LoadMonsterTextures(); // Load monster textures
    void LoadOtherTextures(); // Load all other textures
    static std::string TextureNameToString(TextureName name);
public:
    TextureManager();
    static TextureManager* GetInstance(); // Get the TextureManager instance
    void LoadTextures(); // Load all textures
    GameTexture GetTexture(TextureName textureName); // Get a texture by name
    ~TextureManager();
};

#endif //PLATFORMER_TEXTUREMANAGER_H
