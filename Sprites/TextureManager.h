//
// Created by ben on 5/18/24.
//

#ifndef PLATFORMER_TEXTUREMANAGER_H
#define PLATFORMER_TEXTUREMANAGER_H

#include <map>
#include <string>
#include "raylib.h"

#define PLAYER_TEXTURE_IDLE_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Character/Idle/Idle-Sheet.png"
#define BACKGROUND_TEXTURE_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Background/Background.png"

struct GameTexture {
    Texture2D texture;
    Rectangle rect;
};

class TextureManager {
private:
    static std::map<std::string, GameTexture> Textures;
public:
    TextureManager();
    static void LoadTextures();
    static GameTexture GetTexture(const std::string& texture);
};

#endif //PLATFORMER_TEXTUREMANAGER_H
