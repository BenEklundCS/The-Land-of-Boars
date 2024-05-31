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
#define PLAYER_TEXTURE_IDLE_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Character/Idle/Idle-Sheet.png"
#define PLAYER_TEXTURE_RUNNING_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Character/Run/Run-Sheet.png"
#define PLAYER_TEXTURE_JUMPING_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Character/Jumlp-All/Jump-All-Sheet.png"

// Background path
#define BACKGROUND_TEXTURE_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Background/Background.png"

// Player strings
#define PLAYER_IDLE_TEXTURE "playerIdleTexture"
#define PLAYER_RUNNING_TEXTURE "playerRunningTexture"
#define PLAYER_JUMPING_TEXTURE "playerJumpingTexture"

// Background string
#define BACKGROUND_TEXTURE "backgroundTexture"

// Player frame counts
#define PLAYER_IDLE_FRAMES 4
#define PLAYER_RUNNING_FRAMES 8
#define PLAYER_JUMPING_FRAMES 15

#define BOAR_RUNNING_FRAMES 6

// Player Spritesheet offsets
#define PLAYER_IDLESHEET_OFFSET (-16)
#define PLAYER_RUNSHEET_OFFSET (-12)

// Boar stuff
#define BOAR_TEXTURE_RUNNING_PATH_WHITE "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Mob/Boar/Run/Run-Sheet-White.png"
#define BOAR_RUNNING_TEXTURE_WHITE "boarTextureWhite"

// Tiles
#define TILE_TEXTURE_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Assets/Tiles.png" // Texture path
#define TILE_GRASS_TEXTURE "tileGrassTexture"
#define TILE_DIRT_TEXTURE "tileDirtTexture"

#define TILE_LENGTH 80 // Offset for finding tiles on the sprite sheet

struct GameTexture {
    Texture2D texture;
    Rectangle rect;
};

// Texture Manager loads all textures as a Singleton, and has a GetTexture method to retrieve loaded texture objects
class TextureManager {
private:
    static std::unique_ptr<TextureManager> instance;
    std::map<std::string, GameTexture> Textures;
    void LoadAnimatedTexture(const char * filePath, int offset, int frames, const std::string& textureName);
    void LoadTexture(Texture2D texture, const std::string& textureName, Rectangle rect);
    void Emplace(const std::string& textureName, GameTexture gameTexture);
    void LoadPlayerTextures();
    void LoadTileTextures();
    void LoadMonsterTextures();
    void LoadOtherTextures();
public:
    TextureManager();
    static TextureManager* GetInstance();
    void LoadTextures();
    GameTexture GetTexture(const std::string& texture);
    ~TextureManager();
};

#endif //PLATFORMER_TEXTUREMANAGER_H
