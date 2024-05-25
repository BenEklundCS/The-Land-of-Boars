//
// Created by ben on 5/18/24.
//

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
#define PLAYER_IDLESHEET_OFFSET -16
#define PLAYER_RUNSHEET_OFFSET -12

// Boar stuff
#define BOAR_TEXTURE_RUNNING_PATH_WHITE "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Mob/Boar/Run/Run-Sheet-White.png"
#define BOAR_RUNNING_TEXTURE_WHITE "boarTextureWhite"

struct GameTexture {
    Texture2D texture;
    Rectangle rect;
};

class TextureManager {
private:
    static std::unique_ptr<TextureManager> instance;
    std::map<std::string, GameTexture> Textures;
public:
    TextureManager();
    static TextureManager* GetInstance();
    void LoadTextures();
    GameTexture GetTexture(const std::string& texture);
    ~TextureManager();
};

#endif //PLATFORMER_TEXTUREMANAGER_H
