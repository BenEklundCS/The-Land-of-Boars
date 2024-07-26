//
// Created by ben on 7/25/24.
//

#ifndef PLATFORMER_SOUNDMANAGER_H
#define PLATFORMER_SOUNDMANAGER_H

#include <map>
#include <string>
#include "raylib.h"

class SoundManager {
private:
    std::map<std::string, Sound> sounds;
public:
    void PlaySound(std::string sound_name);
    void LoadSounds();
};

#endif //PLATFORMER_SOUNDMANAGER_H
