//
// Created by ben on 5/18/24.
//

/*
 * The following is essentially a hardcoded texture loader with hardcoded paths to my development directory
 * This must be refactored to find resources dynamically on the target machine at some point
 *
 */

#ifndef PLATFORMER_TEXTUREMANAGER_H
#define PLATFORMER_TEXTUREMANAGER_H

#include <memory>
#include <map>
#include <string>
#include "raylib.h"

// Player paths
#define PLAYER_TEXTURE_IDLE_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Sprites/Character/Idle/Idle-Sheet.png"
#define PLAYER_TEXTURE_RUNNING_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Sprites/Character/Run/Run-Sheet.png"
#define PLAYER_TEXTURE_JUMPING_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Sprites/Character/Jumlp-All/Jump-All-Sheet.png"
#define PLAYER_TEXTURE_ATTACKING_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Sprites/Character/Attack-01/Attack-01-Sheet.png"

// Background path
#define BACKGROUND_TEXTURE_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Sprites/Background/Background.png"

// Player strings
#define PLAYER_IDLE_TEXTURE "playerIdleTexture"
#define PLAYER_RUNNING_TEXTURE "playerRunningTexture"
#define PLAYER_JUMPING_TEXTURE "playerJumpingTexture"
#define PLAYER_ATTACKING_TEXTURE "playerAttackingTexture"

// Background string
#define BACKGROUND_TEXTURE "backgroundTexture"

// Player frame counts
#define PLAYER_IDLE_FRAMES 4
#define PLAYER_RUNNING_FRAMES 8
#define PLAYER_JUMPING_FRAMES 15
#define PLAYER_ATTACKING_FRAMES 8

#define BOAR_RUNNING_FRAMES 6

// Player Spritesheet offsets
#define PLAYER_IDLESHEET_OFFSET (-16)
#define PLAYER_RUNSHEET_OFFSET (-12)

// Boar stuff
#define BOAR_TEXTURE_RUNNING_PATH_WHITE "/home/ben/Programming/Raylib/Platformer/Assets/Sprites/Mob/Boar/Run/Run-Sheet-White.png"
#define BOAR_RUNNING_TEXTURE_WHITE "boarTextureWhite"

// Tiles
#define TILE_TEXTURE_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Sprites/Assets/Tiles.png" // Texture path
#define TILE_GRASS_TEXTURE "tileGrassTexture"
#define TILE_DIRT_TEXTURE "tileDirtTexture"

#define TILE_LENGTH 80 // size of a tile
#define TILE_OFFSET 10 // starting offset to get tile from spritesheet

struct GameTexture {
    Texture2D texture;
    Rectangle rect;
};

// Texture Manager loads all textures as a Singleton, and has a GetTexture method to retrieve loaded texture objects
class TextureManager {
private:
    static std::unique_ptr<TextureManager> instance; // Instance of texture manager
    std::map<std::string, GameTexture> Textures; // Map of textures
    void LoadAnimatedTexture(const char * filePath, int offset, int frames, const std::string& textureName);
    void LoadTexture(Texture2D texture, const std::string& textureName, Rectangle rect); // Load a texture
    void Emplace(const std::string& textureName, GameTexture gameTexture); // Emplace a texture into the texture map
    void LoadPlayerTextures(); // Load player textures
    void LoadTileTextures(); // Load tile textures
    void LoadMonsterTextures(); // Load monster textures
    void LoadOtherTextures(); // Load all other textures
public:
    TextureManager();
    static TextureManager* GetInstance(); // Get the TextureManager instance
    void LoadTextures(); // Load all textures
    GameTexture GetTexture(const std::string& texture); // Get a texture by name
    ~TextureManager();
};

#endif //PLATFORMER_TEXTUREMANAGER_H
