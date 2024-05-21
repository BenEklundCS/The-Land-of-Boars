//
// Created by ben on 5/18/24.
//

#ifndef PLATFORMER_TEXTUREMANAGER_H
#define PLATFORMER_TEXTUREMANAGER_H

#include <memory>
#include <map>
#include <string>
#include "raylib.h"

#define PLAYER_TEXTURE_IDLE_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Character/Idle/Idle-Sheet.png"
#define PLAYER_TEXTURE_RUNNING_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Character/Run/Run-Sheet.png"
#define PLAYER_TEXTURE_JUMPING_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Character/Jumlp-All/Jump-All-Sheet.png"
#define BACKGROUND_TEXTURE_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Background/Background.png"

#define PLAYER_IDLE_TEXTURE "playerIdleTexture"
#define PLAYER_RUNNING_TEXTURE "playerRunningTexture"
#define PLAYER_JUMPING_TEXTURE "playerJumpingTexture"

#define PLAYER_IDLE_FRAMES 4
#define PLAYER_RUNNING_FRAMES 8
#define PLAYER_JUMPING_FRAMES 15

#define PLAYER_IDLESHEET_OFFSET -16
#define PLAYER_RUNSHEET_OFFSET -12

#define BACKGROUND_TEXTURE "backgroundTexture"

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
