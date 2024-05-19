//
// Created by ben on 5/18/24.
//

#ifndef PLATFORMER_TEXTUREMANAGER_H
#define PLATFORMER_TEXTUREMANAGER_H

#include "map"
#include "string"
#include "raylib.h"

#define PLAYER_TEXTURE_IDLE_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Character/Idle/Idle-Sheet.png"
#define BACKGROUND_TEXTURE_PATH "/home/ben/Programming/Raylib/Platformer/Assets/Fantasy/Background/Background.png"

class TextureManager {
private:
    static std::map<std::string, Texture2D> Textures;
    static std::map<std::string, Rectangle> Rects;
public:
    TextureManager();
    static void LoadTextures();
    static Texture2D GetTexture(const std::string& texture);
    static Rectangle GetRect(const std::string& rect);
};


#endif //PLATFORMER_TEXTUREMANAGER_H
